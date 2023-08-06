#include "bsdfs/IsotropicPhaseBSDF.h"
#include <cmath>
#include "Utility.h"

IsotropicPhaseBSDF::IsotropicPhaseBSDF(const Computation& comp) : BSDF(comp) {}

IsotropicPhaseBSDF::~IsotropicPhaseBSDF() {}

void IsotropicPhaseBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf)
{
    pdf = 0.25 / M_PI;
    L = ngl::Vec3(pdf, pdf, pdf);
}

void IsotropicPhaseBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    auto xi = randomDouble(); 
    sampleDirection.m_z = xi * 2.0f - 1.0f;
    float sinTheta = 1.0f - sampleDirection.m_z * sampleDirection.m_z;

    if (sinTheta > 0.0f)
    {
        sinTheta = std::sqrt(sinTheta);
        xi = randomDouble();
        float phi = xi * 2.0f * M_PI;
        sampleDirection.m_x = sinTheta * std::cos(phi);
        sampleDirection.m_y = sinTheta * std::sin(phi);
    }
    else
    {
        sampleDirection.m_x = sampleDirection.m_y = 0.0f;
    }
    
    pdf = 0.25f / M_PI;
    L = ngl::Vec3(pdf, pdf, pdf);
}
