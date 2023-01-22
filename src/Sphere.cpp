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

bool Sphere::operator==(const Sphere& other) const
{
    return m_id == other.m_id &&
    m_transform == other.m_transform &&
    m_material == other.m_material;
}

bool Sphere::operator!=(const Sphere& other) const
{
    return m_id != other.m_id ||
    !(m_transform == other.m_transform) ||
    !(m_material == other.m_material);
}

/// @brief ray intersecting sphere
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
std::vector<Intersection> Sphere::intersect(Ray _r)
{
    
    Ray _r2 = _r.transform(m_transform.inverse());

    std::vector<Intersection> intersection;

    auto sphereToArray = _r2.origin() - ngl::Vec3(0.0f, 0.0f, 0.0f);
    auto a = _r2.direction().dot(_r2.direction());
    auto b = 2 * (_r2.direction().dot(sphereToArray));
    auto c = sphereToArray.dot(sphereToArray) - 1;

    auto discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant >= 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2 *a);
        auto i1 = Intersection(t1, this);
        intersection.push_back(i1);
        float t2 = (-b + std::sqrt(discriminant)) / (2 *a);
        auto i2 = Intersection(t2, this);
        intersection.push_back(i2);
    }
    return intersection;
}

ngl::Mat4 Sphere::transform()
{
    return m_transform;
}

void Sphere::setTransform(ngl::Mat4 _tMatrix)
{
    auto newTransform = _tMatrix * m_transform;
    m_transform = newTransform;
}

int Sphere::id() const
{
    return m_id;
}

Material Sphere::material()
{
    return m_material;
}

void Sphere::material(Material _m)
{
    m_material = _m;
}

/// @brief normal vector at a point
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
ngl::Vec4 Sphere::normalAt(ngl::Vec4 _worldPoint)
{
    auto objPoint = m_transform.inverse() * _worldPoint;
    auto objNormal = objPoint - ngl::Vec4(0.0f,0.0f,0.0f);
    auto worldNormal = (m_transform.inverse()).transpose() * objNormal;
    worldNormal.m_w = 0.0f;
    return worldNormal.normalize();
}
/// end of Citation