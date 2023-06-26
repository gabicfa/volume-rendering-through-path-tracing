#ifndef TESTSHAPE_H_
#define TESTSHAPE_H_

#include "Shape.h"
class Ray;
class Intersection;

class TestShape : public Shape
{
public:
    TestShape();

    bool operator==(const Shape& other) const override;
    bool operator!=(const Shape& other) const override;
    ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
    std::vector<Intersection> localIntersect(Ray _r) override;        

};

#endif
