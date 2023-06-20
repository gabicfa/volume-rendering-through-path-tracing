#ifndef TESTSHAPE_H_
#define TESTSHAPE_H_

#include "Shape.h"

class TestShape : public Shape
{
public:
    TestShape();

    std::vector<Intersection> intersect(Ray _r) override;
    bool operator==(const Shape& other) const override;
    bool operator!=(const Shape& other) const override;
    ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
};

#endif
