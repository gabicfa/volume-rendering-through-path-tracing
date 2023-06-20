#include "TestShape.h"

TestShape::TestShape()
{
}

std::vector<Intersection> TestShape::intersect(Ray _r)
{
    return std::vector<Intersection>();
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