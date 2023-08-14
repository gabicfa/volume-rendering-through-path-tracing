#include "AreaLight.h"
#include <random>

AreaLight::AreaLight(const ngl::Vec4& _center, const ngl::Vec4& _udir, const ngl::Vec4& _vdir, const ngl::Vec3& _intensity)
    : m_center(_center), m_udir(_udir), m_vdir(_vdir), m_intensity(_intensity) {}

ngl::Vec4 AreaLight::udir() const 
{ 
    return m_udir; 
}

ngl::Vec4 AreaLight::vdir() const 
{ 
    return m_vdir; 
}

ngl::Vec4 AreaLight::center() const 
{
    return m_center; 
}

ngl::Vec3 AreaLight::intensity() const 
{ 
    return m_intensity; 
}

// Method to sample a random point on the area light's surface.
// Outputs the sampled point's position and the light's intensity at that point.
void AreaLight::sample(ngl::Vec4& _samplePoint, ngl::Vec3& _intensity) const
{
    // Set up random number generation.
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);

    // Generate a random point on the area light's surface.
    _samplePoint = m_center + dis(gen) * m_udir + dis(gen) * m_vdir;
    
    // Set the intensity to the area light's intensity.
    _intensity = m_intensity;
}
