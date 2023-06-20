#include "Sphere.h"

Sphere::Sphere()
{
    m_id = 0;
    m_transform = ngl::Mat4();
    m_material = Material();
}

Sphere::Sphere(int _id)
{
    m_id = _id;
}

bool Sphere::operator==(const Shape& other) const
{
    if (const Sphere* sphere = dynamic_cast<const Sphere*>(&other))
    {
        return m_id == sphere->m_id &&
               m_transform == sphere->m_transform &&
               m_material == sphere->m_material;
    }
    return false;
}

bool Sphere::operator!=(const Shape& other) const
{
    if (const Sphere* sphere = dynamic_cast<const Sphere*>(&other))
    {
        return m_id != sphere->m_id ||
           !(m_transform == sphere->m_transform) ||
           !(m_material == sphere->m_material);
    }
    return false;
}

std::vector<Intersection> Sphere::intersect(Ray _r)
{
    auto local_ray = _r.transform(m_transform.inverse());
    return localIntersect(local_ray);
}

/// @brief ray intersecting sphere
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
std::vector<Intersection> Sphere::localIntersect(Ray _r)
{
    std::vector<Intersection> intersection;

    auto sphereToArray = _r.origin() - ngl::Vec3(0.0f, 0.0f, 0.0f);
    auto a = _r.direction().dot(_r.direction());
    auto b = 2 * (_r.direction().dot(sphereToArray));
    auto c = sphereToArray.dot(sphereToArray) - 1;

    auto discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant >= 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2 * a);
        auto i1 = Intersection(t1, std::make_shared<Sphere>(*this));
        intersection.push_back(i1);
        float t2 = (-b + std::sqrt(discriminant)) / (2 * a);
        auto i2 = Intersection(t2, std::make_shared<Sphere>(*this));
        intersection.push_back(i2);
    }
    return intersection;
}

ngl::Mat4 Sphere::transform() const
{
    return m_transform;
}

void Sphere::setTransform(const ngl::Mat4& _tMatrix)
{
    m_transform =  m_transform * _tMatrix;
}

int Sphere::id() const
{
    return m_id;
}

Material Sphere::material() const
{
    return m_material;
}

void Sphere::setMaterial(const Material& _m)
{
    m_material = _m;
}

ngl::Vec4 Sphere::normalAt(ngl::Vec4 _worldPoint)
{
    auto objPoint = m_transform.inverse() * _worldPoint;
    auto objNormal = localNormalAt(objPoint);
    auto worldNormal = (m_transform.inverse()).transpose() * objNormal;
    worldNormal.m_w = 0.0f;
    return worldNormal.normalize();
}

/// @brief normal vector at a point
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
ngl::Vec4 Sphere::localNormalAt(ngl::Vec4 _localPoint)
{
    return _localPoint - ngl::Vec4(0.0f,0.0f,0.0f);
}
/// end of Citation