#include "RendererServices.h"
#include "Scene.h"
#include "Material.h"
#include "Volume.h"
#include "Intersection.h"

RendererServices::RendererServices(AreaLight _light) : m_light(_light)
{
}

float RendererServices::MISWeight(int nsamps1, float pdf1, int nsamps2, float pdf2) {
    float s1 = nsamps1 * pdf1;
    float s2 = nsamps2 * pdf2;
    return s1 / (s1 + s2);
}

void RendererServices::generateLightSample(const Computation &_comp, ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance, Scene &scene) 
{
    
    ngl::Vec4 samplePoint;
    m_light.sample(samplePoint, L);
    L = m_light.intensity();
    ngl::Vec4 lightToSurface = samplePoint - _comp.point;
    lightToSurface.normalize();
    sampleDirection = lightToSurface;

    float lightArea = m_light.udir().length() * m_light.vdir().length();
    float distanceSquared = lightToSurface.lengthSquared();

    auto normalToLightPlane = m_light.udir().cross(m_light.vdir());
    normalToLightPlane.normalize();

    pdf = distanceSquared / (lightArea * std::abs(sampleDirection.dot(normalToLightPlane)));

    auto [occluded, transmittance] = computeTransmittance(_comp.point, _comp.point + sampleDirection, scene);
    beamTransmittance = transmittance;
}

void RendererServices::evaluateLightSample(const Computation &_comp, const ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance, Scene &scene)
{
    auto m = _comp.matPtr;
    auto bsdf = m->createBSDF(_comp);

    ngl::Vec3 evaluatedColor;
    bsdf->evaluateSample(_comp, sampleDirection, evaluatedColor, pdf);
    L = evaluatedColor;

    if (sampleDirection.dot(_comp.normal) > 0) {
        float lightArea = m_light.udir().length() * m_light.vdir().length();
        float distanceSquared = (m_light.center() - _comp.point).lengthSquared();
        auto normalToLightPlane = m_light.udir().cross(m_light.vdir());
        normalToLightPlane.normalize();
        pdf = distanceSquared / (lightArea * std::abs(sampleDirection.dot(normalToLightPlane)));
    } else {
        pdf = 0.0f;
    }

    auto [occluded, transmittance] = computeTransmittance(_comp.point, _comp.point + sampleDirection, scene);
    beamTransmittance = transmittance;
}

void RendererServices::evaluateLightSample(const Computation &_comp, const ngl::Vec3 &sampleDirection, ngl::Vec3 &L, float &pdf)
{
    auto m = _comp.matPtr;
    auto bsdf = m->createBSDF(_comp);

    ngl::Vec3 evaluatedColor;
    bsdf->evaluateSample(_comp, sampleDirection, evaluatedColor, pdf);
    L = evaluatedColor;
}

std::pair<bool, ngl::Vec3> RendererServices::computeTransmittance(const ngl::Vec4 &start, const ngl::Vec4 &end, Scene &scene)
{
    auto direction = end - start;
    float distance = direction.length();
    direction.normalize();

    ngl::Vec4 offsetStart = start + 0.001f * direction;
    Ray shadowRay(offsetStart, direction);

    auto intersections = scene.intersectScene(shadowRay);
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    ngl::Vec3 transmittance(1.0f, 1.0f, 1.0f);
    bool isOccluded = i != Intersection();
    if (i != Intersection())
    {
        auto comp = i.prepareComputations(shadowRay);
        auto m = comp.matPtr;
        if (m->hasVolume()) 
        {
            ngl::Vec3 accumulatedTransmittance(1.0f, 1.0f, 1.0f);
            float dirDotN = shadowRay.direction().dot(comp.normal);
            bool entered = dirDotN < 0.0f;
            if (entered) {
                shadowRay.enterMaterial(m);
            } else {
                shadowRay.exitMaterial(m);
            }
            
            auto volume = shadowRay.getVolume(comp);
            ngl::Vec4 P0 = comp.point;

            auto nextI = Intersection::nextHitAfter(i, xs);

            if (volume != nullptr && nextI != Intersection()) {
                // Calculate transmittance for the segment using the current volume properties
                auto compI = nextI.prepareComputations(shadowRay);
                auto P1 = compI.point;
                ngl::Vec3 segmentTransmittance = volume->transmittance(P0, P1);
                
                // Multiply accumulated transmittance with the current segment's transmittance
                accumulatedTransmittance = accumulatedTransmittance * segmentTransmittance;
            }
            transmittance = accumulatedTransmittance;
            isOccluded = false;
            }
            
        else {
            isOccluded = true;
        }
    }
    return {isOccluded, transmittance};
}