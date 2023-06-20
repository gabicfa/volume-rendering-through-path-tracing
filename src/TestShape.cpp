#include "TestShape.h"

TestShape::TestShape()
{
}

int TestShape::id() const
{
    return 0;
}

ngl::Mat4 TestShape::transform() const
{
    return ngl::Mat4();
}

void TestShape::setTransform(const ngl::Mat4& _tMatrix)
{
}

Material TestShape::material() const
{
    return Material();
}

void TestShape::setMaterial(const Material& _m)
{
}

std::vector<Intersection> TestShape::intersect(Ray _r)
{
    return std::vector<Intersection>();
}

ngl::Vec4 TestShape::normalAt(ngl::Vec4 _worldPoint)
{
    return ngl::Vec4();
}

bool TestShape::operator==(const Shape& other) const
{
    return true;
}

bool TestShape::operator!=(const Shape& other) const
{
    return false;
}