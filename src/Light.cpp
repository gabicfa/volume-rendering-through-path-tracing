#include "Light.h"

Light::Light()
{

}

Light::Light(ngl::Vec3 _i, ngl::Vec4 _p) : m_intensity{_i}, m_position{_p}
{

}
ngl::Vec3 Light::intensity() const
{
    return m_intensity;
}

ngl::Vec4 Light::position() const
{
    return m_position;
}

bool Light::operator==(const Light& other) const
{
    return m_intensity == other.intensity() && m_position == other.position();
}