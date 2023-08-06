#include "bsdfs/LightEmittingBSDF.h"

LightEmittingBSDF::LightEmittingBSDF(const Computation& _comp) 
    : BSDF(_comp) {}

LightEmittingBSDF::~LightEmittingBSDF() {}

void LightEmittingBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    // Emitting light doesn't really scatter rays, so we don't generate any samples
    sampleDirection = ngl::Vec4(0, 0, 0, 0);
    L = ngl::Vec3(0, 0, 0);
    pdf = 0;
}

void LightEmittingBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    // Emitting light doesn't really scatter rays, so we return L as zero and pdf as zero
    L = ngl::Vec3(0, 0, 0);
    pdf = 0;
}
