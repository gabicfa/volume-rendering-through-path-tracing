#include "TestShape.h"
#include "Ray.h"
#include "Intersection.h"
#include "Material.h"

TestShape::TestShape()
{
}

TestShape::TestShape(int _id, std::shared_ptr<Material> _matPtr)
{
    this->id(_id);
    this->setMaterial(_matPtr);
}

bool TestShape::operator==(const Shape& other) const
{
    return true;
}

bool TestShape::operator!=(const Shape& other) const
{
    return false;
}

// Returns the local normal at a given point on the TestShape.
// In this generic test implementation, the local point itself is returned as the normal.
ngl::Vec4 TestShape::localNormalAt(ngl::Vec4 _localPoint)
{
    return _localPoint;
}

// Computes the local intersections of a ray with the TestShape.
// This generic test implementation returns an empty list of intersections.
std::vector<Intersection> TestShape::localIntersect(Ray _r)
{
    std::vector<Intersection> intersections;
    return intersections;
}
