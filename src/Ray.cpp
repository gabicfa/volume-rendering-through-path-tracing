#include "Ray.h"

Ray::Ray(ngl::Vec3 _origin, ngl::Vec3 _direction)
{
    m_origin = _origin;
    m_direction = _direction;
}

ngl::Vec3 Ray::origin() const
{
    return m_origin;
}

ngl::Vec3 Ray::direction() const
{
    return m_direction;
}

ngl::Vec3 Ray::position(float _t)
{
    return m_origin + m_direction * _t;
}
