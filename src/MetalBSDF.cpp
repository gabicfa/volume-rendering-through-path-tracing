#include "MetalBSDF.h"
#include "Utility.h"
#include "Material.h"

MetalBSDF::MetalBSDF(const Computation& _comp) 
    : BSDF(_comp) {}

MetalBSDF::~MetalBSDF() {}

void MetalBSDF::generateSample(const Computation& _comp, ngl::Vec3& sampleDirection, ngl::Vec3& L, float& pdf)
{
    sampleDirection = unitVector(_comp.incomingRay.direction()).toVec3().reflect(_comp.normal.toVec3());
    ngl::Vec3 albedo = _comp.matPtr->albedo().toVec3();
    L = albedo;
    pdf = 1.0;
}

void MetalBSDF::evaluateSample(const Computation& _comp, const ngl::Vec3& sampleDirection, ngl::Vec3& L, float& pdf)
{
    ngl::Vec3 reflectedDirection = unitVector(_comp.incomingRay.direction()).toVec3().reflect(_comp.normal.toVec3());
    if (sampleDirection == reflectedDirection)
    {
        ngl::Vec3 albedo = _comp.matPtr->albedo().toVec3();
        L = albedo;
        pdf = 1.0;
    }
    else
    {
        L = ngl::Vec3(0.0, 0.0, 0.0);
        pdf = 0.0;
    }
}