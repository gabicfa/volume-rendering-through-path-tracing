#include "AreaLight.h"
#include <random>

AreaLight::AreaLight(const ngl::Vec4& _center, const ngl::Vec4& _udir, const ngl::Vec4& _vdir, const ngl::Vec3& _intensity)
    : m_center(_center), m_udir(_udir), m_vdir(_vdir), m_intensity(_intensity) {}

ngl::Vec4 AreaLight::udir() const { return m_udir; }
ngl::Vec4 AreaLight::vdir() const { return m_vdir; }
ngl::Vec4 AreaLight::center() const { return m_center; }
ngl::Vec3 AreaLight::intensity() const { return m_intensity; }

void AreaLight::sample(ngl::Vec4& _samplePoint, ngl::Vec3& _intensity) const
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<> dis(-1.0, 1.0);
    _samplePoint = m_center + dis(gen) * m_udir + dis(gen) * m_vdir;
    _intensity = m_intensity;
}
