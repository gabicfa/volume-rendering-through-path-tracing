#include "bsdfs/LightEmittingBSDF.h"

LightEmittingBSDF::LightEmittingBSDF(const Computation& _comp) 
    : BSDF(_comp) {}

LightEmittingBSDF::~LightEmittingBSDF() {}

// For light-emitting surfaces, we don't scatter or generate samples as they are sources of light.
// Hence, set sample direction and the radiance (L) to zero. Probability density function (pdf) is also set to zero.
void LightEmittingBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    sampleDirection = ngl::Vec4(0, 0, 0, 0);
    L = ngl::Vec3(0, 0, 0);
    pdf = 0;
}

// For light-emitting surfaces, there's no light to scatter. Hence, radiance (L) is returned as zero 
// and probability density function (pdf) is also set to zero.
void LightEmittingBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    L = ngl::Vec3(0, 0, 0);
    pdf = 0;
}
