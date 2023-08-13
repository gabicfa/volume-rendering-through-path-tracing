#include "bsdfs/MetalBSDF.h"
#include "Utility.h"
#include "Material.h"

MetalBSDF::MetalBSDF(const Computation& _comp) 
    : BSDF(_comp) {}

MetalBSDF::~MetalBSDF() {}

// Generates a reflected sample direction for the metallic surface based on the incident ray's direction.
void MetalBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    // Reflect the incoming ray's direction across the surface normal to get the sample direction.
    // In idealized metal surfaces, rays are perfectly reflected without diffusion.
    sampleDirection = unitVector(_comp.incomingRay.direction()).toVec3().reflect(_comp.normal.toVec3());

    // The reflection's intensity (L) is set to the material's albedo.
    ngl::Vec3 albedo = _comp.matPtr->albedo().toVec3();
    L = albedo;

    // The PDF is set to 1 because for an idealized metal surface, there's only one possible reflection direction.
    pdf = 1.0;
}

// Evaluates the reflection of the metallic surface for a given sample direction. 
void MetalBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    // Predict the direction a ray would be reflected in.
    ngl::Vec3 reflectedDirection = unitVector(_comp.incomingRay.direction()).toVec3().reflect(_comp.normal.toVec3());

    // If the provided sample direction matches the predicted reflection direction, it means the light
    // is contributing to the reflection we're observing.
    if (sampleDirection == reflectedDirection)
    {
        // The reflection's intensity (L) is set to the material's albedo.
        ngl::Vec3 albedo = _comp.matPtr->albedo().toVec3();
        L = albedo;

        // The PDF is set to 1 because for an idealized metal surface, there's only one possible reflection direction.
        pdf = 1.0;
    }
    else
    {
        // If the sample direction doesn't match the predicted reflection direction, there's no contribution 
        // from the sample direction. Hence, the light intensity (L) is set to zero and the PDF is also zero.
        L = ngl::Vec3(0.0, 0.0, 0.0);
        pdf = 0.0;
    }
}
