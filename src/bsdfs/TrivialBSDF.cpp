#include "bsdfs/TrivialBSDF.h"

TrivialBSDF::TrivialBSDF(const Computation& comp) : BSDF(comp) {}

TrivialBSDF::~TrivialBSDF() {}

/// @brief  TrivialBSDF class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// For this BSDF, the radiance (L) resulting from any sample direction is always zero
// since the material simply absorbs light without any reflection or refraction.
// The Probability Density Function (pdf) is set to zero, indicating there's no preference for any specific direction.
void TrivialBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf)
{
    pdf = 0.0;
    L = ngl::Vec3(0.0, 0.0, 0.0);
}

// The GenerateSample method continues a ray in the outgoing direction with full weight (radiance L set to white)
// and a Probability Density Function (pdf) of 1, indicating certainty in the continued direction.
void TrivialBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    auto _compEye = m_comp.eye;
    sampleDirection = -_compEye;
    pdf = 1.0;
    L = ngl::Vec3(1.0, 1.0, 1.0);
}

//end of citation
