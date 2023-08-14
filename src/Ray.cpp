#include "Ray.h"
#include "Material.h"
#include "Computation.h"
#include "Volume.h"
#include <algorithm>

Ray::Ray() 
    : m_origin(ngl::Vec4(0,0,0,0)), m_direction(ngl::Vec4(0,0,0,0)) {}

Ray::Ray(ngl::Vec4 _origin, ngl::Vec4 _direction)
    : m_origin(_origin), m_direction(_direction) {}

// Copy constructor implementation.
Ray::Ray(const Ray &ray)
    : m_origin(ray.m_origin), m_direction(ray.m_direction), m_volumes(ray.m_volumes) {}

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

// Transform the ray using a given matrix and return the new ray.
Ray Ray::transform(ngl::Mat4 _tMatrix)
{
    auto newOrigin = _tMatrix * m_origin;
    auto newDirection = m_direction * _tMatrix;
    Ray newRay(newOrigin, newDirection);
    newRay.m_volumes = this->m_volumes;
    return newRay;
}

// Add a volume to the ray's encountered stack.
void Ray::enterMaterial(std::shared_ptr<Material> b)
{
    m_volumes.push_back(b);
}

// Remove a volume from the ray's encountered stack.
void Ray::exitMaterial(std::shared_ptr<Material> b)
{
    m_volumes.erase(std::remove(m_volumes.begin(), m_volumes.end(), b), m_volumes.end());
}

/// @brief Retrieve the last volume the ray has encountered, if any.
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.
std::shared_ptr<Volume> Ray::getVolume(Computation &_comp) const
{
    if (!m_volumes.empty())
        return (*m_volumes.rbegin())->createVolume(_comp);
    else
        return nullptr;
}
/// end of Citation
