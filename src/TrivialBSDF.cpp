#include "TrivialBSDF.h"

TrivialBSDF::TrivialBSDF(const Computation& comp) : BSDF(comp) {}

TrivialBSDF::~TrivialBSDF() {}

void TrivialBSDF::evaluateSample(const Computation& _comp, const ngl::Vec3& sampleDirection, ngl::Vec3& L, float &pdf)
{
    pdf = 0.0;
    L = ngl::Vec3(0.0, 0.0, 0.0);
}

void TrivialBSDF::generateSample(const Computation& _comp, ngl::Vec3& sampleDirection, ngl::Vec3& L, float& pdf)
{
    auto _compEye = m_comp.eye;
    sampleDirection = -_compEye;
    pdf = 1.0;
    L = ngl::Vec3(1.0, 1.0, 1.0);
}
