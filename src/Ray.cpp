#include "Ray.h"

Ray::Ray(ngl::Vec4 _origin, ngl::Vec4 _direction)
{
    m_origin = _origin;
    m_direction = _direction;
}

ngl::Vec4 Ray::origin() const
{
    return m_origin;
}

ngl::Vec4 Ray::direction() const
{
    return m_direction;
}

ngl::Vec4 Ray::position(float _t)
{
    return m_origin + m_direction * _t;
}

Ray Ray::transform(ngl::Mat4 _tMatrix)
{
    auto newOrigin = _tMatrix * m_origin;
    auto newDirection = m_direction * _tMatrix;
    auto newRay = Ray(newOrigin, newDirection);
    return newRay;
}
