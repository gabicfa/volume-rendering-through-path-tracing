#include "TestShape.h"

TestShape::TestShape()
{
}

bool TestShape::operator==(const Shape& other) const
{
    return true;
}

bool TestShape::operator!=(const Shape& other) const
{
    return false;
}

ngl::Vec4 TestShape::localNormalAt(ngl::Vec4 _localPoint)
{
    return _localPoint;
}

std::vector<Intersection> TestShape::localIntersect(Ray _r)
{
    std::vector<Intersection> intersections;
    return intersections;
}