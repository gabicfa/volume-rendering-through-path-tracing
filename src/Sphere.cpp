#include "Sphere.h"
#include "Utility.h"
#include "Ray.h"
#include "Material.h"
#include "Intersection.h"

Sphere::Sphere()
{
}

Sphere::Sphere(int _id)
{
    this->id(_id);
}

Sphere::Sphere(int _id, std::shared_ptr<Material> _matPtr)
{
    this->id(_id);
    this->setMaterial(_matPtr);
}

// Equality operator checks if two spheres (or a sphere and another shape) are identical based on their IDs and transformations.
bool Sphere::operator==(const Shape& other) const
{
    if (const Sphere* sphere = dynamic_cast<const Sphere*>(&other))
    {
        return id() == sphere->id() &&
               transform() == sphere->transform();
    }
    return false;
}

// Inequality operator leverages the equality operator to determine if two spheres are different.
bool Sphere::operator!=(const Shape& other) const
{
    if (const Sphere* sphere = dynamic_cast<const Sphere*>(&other))
    {
        return id() != sphere->id() ||
           !(transform() == sphere->transform());
    }
    return false;
}


/// @brief ray intersecting sphere
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
std::vector<Intersection> Sphere::localIntersect(Ray _r)
{
    // This method calculates the intersections of a ray with the sphere using a quadratic formula approach.
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

/// @brief normal vector at a point
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
ngl::Vec4 Sphere::localNormalAt(ngl::Vec4 _localPoint)
{
    // Calculates the normal vector at a given point on the sphere's surface.
    // The normal is essentially the vector from the sphere's center to the point.
    return _localPoint - ngl::Vec4(0.0f,0.0f,0.0f);
}
/// end of Citation
