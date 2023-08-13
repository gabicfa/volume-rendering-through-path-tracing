#include "bsdfs/IsotropicPhaseBSDF.h"
#include <cmath>
#include "Utility.h"

IsotropicPhaseBSDF::IsotropicPhaseBSDF(const Computation& comp) : BSDF(comp) {}

IsotropicPhaseBSDF::~IsotropicPhaseBSDF() {}

/// @brief  IsotropicPhaseBSDF class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// Evaluates the scattering function for the provided sample direction.
// Since the scattering is isotropic, the pdf is constant (1 / (4 * π)) and 
// the radiance L is based on the pdf value, which represents equal scattering in all directions.
void IsotropicPhaseBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf)
{
    pdf = 0.25 / M_PI;
    L = ngl::Vec3(pdf, pdf, pdf);
}

// Generates a sample direction based on the isotropic phase function.
// The scattering is uniform in all directions, so a random direction is generated.
// The generated direction is based on a uniform sampling of a unit sphere.
// The pdf and radiance L are constant for all directions.
void IsotropicPhaseBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    auto xi = randomDouble(); 
    sampleDirection.m_z = xi * 2.0f - 1.0f;
    float sinTheta = 1.0f - sampleDirection.m_z * sampleDirection.m_z;

    // Convert uniform random samples into spherical coordinates
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

// end of citation