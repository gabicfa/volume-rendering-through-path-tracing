#include "TestShape.h"
#include "Ray.h"
#include "Intersection.h"
#include "AbsMaterial.h"

TestShape::TestShape()
{
}

TestShape::TestShape(int _id, std::shared_ptr<AbsMaterial> _matPtr)
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

ngl::Vec4 TestShape::localNormalAt(ngl::Vec4 _localPoint)
{
    return _localPoint;
}

std::vector<Intersection> TestShape::localIntersect(Ray _r)
{
    std::vector<Intersection> intersections;
    return intersections;
}