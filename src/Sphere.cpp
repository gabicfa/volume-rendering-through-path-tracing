#include "Sphere.h"
#include "Intersection.h"
Sphere::Sphere(int _id)
{
    m_id = _id;
}

bool Sphere::operator==(const Sphere& other) const 
{
    return m_id == other.id();
}

std::vector<Intersection> Sphere::intersect(Ray _r)
{
    std::vector<Intersection> intersection;

    auto sphereToArray = _r.origin() - ngl::Vec3(0.0f, 0.0f, 0.0f);
    auto a = _r.direction().dot(_r.direction());
    auto b = 2 * (_r.direction().dot(sphereToArray));
    auto c = sphereToArray.dot(sphereToArray) - 1;

    auto discriminant = pow(b, 2) - 4 * a * c;

    if (discriminant >= 0)
    {
        float t1 = (-b - std::sqrt(discriminant)) / (2 *a);
        auto i1 = Intersection(t1, this->id());
        intersection.push_back(i1);
        float t2 = (-b + std::sqrt(discriminant)) / (2 *a);
        auto i2 = Intersection(t2, this->id());
        intersection.push_back(i2);
    }
    return intersection;
}

int Sphere::id() const
{
    return m_id;
}