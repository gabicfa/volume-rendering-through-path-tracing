#include "RendererServices.h"
#include "Scene.h"
#include "Material.h"
#include "Volume.h"
#include "Intersection.h"

RendererServices::RendererServices(AreaLight _light) : m_light(_light)
{
}

// Computes the Multiple Importance Sampling (MIS) weight.
// This weight balances the contribution of two different sampling techniques based on their 
// respective number of samples (nsamps1 and nsamps2) and their probability densities (pdf1 and pdf2).
float RendererServices::MISWeight(int nsamps1, float pdf1, int nsamps2, float pdf2) {
    float s1 = nsamps1 * pdf1;  // Combined importance of the first sampling technique.
    float s2 = nsamps2 * pdf2;  // Combined importance of the second sampling technique.

    // The final weight is the ratio of the importance of the first technique 
    // over the sum of the importances of both techniques. This ensures an optimal 
    // balance between both sampling strategies.
    return s1 / (s1 + s2);
}

// Generates a light sample for a given shading context.
// This method samples a direction from the light source towards the shading point, computes the 
// radiance in this direction, the associated probability density of this direction, 
// and the beam transmittance between the light and the shading point
void RendererServices::generateLightSample(const Computation &_comp, ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance, Scene &scene) 
{
    ngl::Vec4 samplePoint;

    // Sample a point on the light source and compute its intensity.
    m_light.sample(samplePoint, L);
    L = m_light.intensity();

    // Compute the direction from the sampled point on the light source to the shading point.
    ngl::Vec4 lightToSurface = samplePoint - _comp.point;
    lightToSurface.normalize();
    sampleDirection = lightToSurface;

    // Compute the probability density function (pdf) of this sampled direction.
    // This computation considers the geometry of the light source (its area) and 
    // the angle between the sampled direction and the light's plane.
    float lightArea = m_light.udir().length() * m_light.vdir().length();
    float distanceSquared = lightToSurface.lengthSquared();
    auto normalToLightPlane = m_light.udir().cross(m_light.vdir());
    normalToLightPlane.normalize();
    pdf = distanceSquared / (lightArea * std::abs(sampleDirection.dot(normalToLightPlane)));

    // Compute the beam transmittance between the light and the shading point.
    // This checks if any objects in the scene are occluding the light and calculates 
    // how much of the light's intensity is transmitted to the shading point.
    auto [occluded, transmittance] = computeTransmittance(_comp.point, _comp.point + sampleDirection, scene);
    beamTransmittance = transmittance;
}

// Evaluates the light's contribution for a given shading context and direction.
// This method determines how much light is received at a shading point from a specific direction 
// taking into account properties of the material at that shading point.
void RendererServices::evaluateLightSample(const Computation &_comp, const ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance, Scene &scene)
{
    // Retrieve the material properties at the shading point.
    auto m = _comp.matPtr;
    auto bsdf = m->createBSDF(_comp);

    // Evaluate the color contribution from the given sample direction using the material's BSDF.
    ngl::Vec3 evaluatedColor;
    bsdf->evaluateSample(_comp, sampleDirection, evaluatedColor, pdf);
    L = evaluatedColor;

    // Check if the sample direction is above the surface. If so, compute the probability density function (pdf)
    // of this direction, considering the geometry of the light source (its area) and the 
    // angle between the sample direction and the light's plane.
    if (sampleDirection.dot(_comp.normal) > 0) 
    {
        float lightArea = m_light.udir().length() * m_light.vdir().length();
        float distanceSquared = (m_light.center() - _comp.point).lengthSquared();
        auto normalToLightPlane = m_light.udir().cross(m_light.vdir());
        normalToLightPlane.normalize();
        pdf = distanceSquared / (lightArea * std::abs(sampleDirection.dot(normalToLightPlane)));
    } 
    else 
    {
        pdf = 0.0f;  // If the direction is below the surface, set the pdf to 0.
    }

    // Compute the beam transmittance between the light and the shading point.
    // This checks if any objects in the scene are occluding the light and calculates 
    // how much of the light's intensity is transmitted to the shading point.
    auto [occluded, transmittance] = computeTransmittance(_comp.point, _comp.point + sampleDirection, scene);
    beamTransmittance = transmittance;
}


// Overloaded version of the above function.
// Omits beam transmittance calculation and works directly with a 3D sample direction.
void RendererServices::evaluateLightSample(const Computation &_comp, const ngl::Vec3 &sampleDirection, ngl::Vec3 &L, float &pdf)
{
    auto m = _comp.matPtr;
    auto bsdf = m->createBSDF(_comp);

    ngl::Vec3 evaluatedColor;
    bsdf->evaluateSample(_comp, sampleDirection, evaluatedColor, pdf);
    L = evaluatedColor;
}

// Calculates the transmittance of light traveling from a start point to an end point within a scene.
// Transmittance represents the fraction of light that makes it through a medium without being absorbed or scattered.
std::pair<bool, ngl::Vec3> RendererServices::computeTransmittance(const ngl::Vec4 &start, const ngl::Vec4 &end, Scene &scene)
{
    // Calculate the direction in which light travels from the start point to the end point.
    auto direction = end - start;
    float distance = direction.length();
    direction.normalize();

    // Offset the start point slightly in the direction of the light to prevent self-shadowing.
    ngl::Vec4 offsetStart = start + 0.001f * direction;
    
    // Create a ray from the offset start point in the light's direction.
    Ray shadowRay(offsetStart, direction);

    // Check for any intersections of the shadow ray with the scene objects.
    auto intersections = scene.intersectScene(shadowRay);
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    // Initialize the transmittance to fully unoccluded (1,1,1).
    ngl::Vec3 transmittance(1.0f, 1.0f, 1.0f);
    bool isOccluded = i != Intersection();

    if (i != Intersection())
    {
        // Compute surface interaction details at the intersection point.
        auto comp = i.prepareComputations(shadowRay);
        auto m = comp.matPtr;
        
        // If the intersected material has volume properties, consider its transmittance.
        if (m->hasVolume()) 
        {
            float dirDotN = shadowRay.direction().dot(comp.normal);
            // Determine if the ray entered or exited the material based on the dot product.
            bool entered = dirDotN < 0.0f;
            if (entered) {
                shadowRay.enterMaterial(m);
            } else {
                shadowRay.exitMaterial(m);
            }
            
            // Retrieve the volume properties of the material at the intersection point.
            auto volume = shadowRay.getVolume(comp);
            ngl::Vec4 P0 = start;
            ngl::Vec4 P1 = comp.point;

            // If there's a volume, compute the transmittance 
            // for the segment between these two points.
            if (volume != nullptr) {
                ngl::Vec3 segmentTransmittance = volume->transmittance(P0, P1);
                transmittance = segmentTransmittance;
            }
            isOccluded = false;
        }
        else {
            // If the material doesn't have volume properties, the ray is occluded.
            isOccluded = true;
        }
    }
    // Return if the ray was occluded and the computed transmittance.
    return {isOccluded, transmittance};
}
