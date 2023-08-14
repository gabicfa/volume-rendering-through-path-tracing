#ifndef TESTSHAPE_H_
#define TESTSHAPE_H_

#include "Shape.h"

class Ray;
class Intersection;
class Material;

// TestShape is a concrete implementation of the Shape class for testing purposes.
// It provides a generic shape to be used during testing of the Shape class functionality.
class TestShape : public Shape
{
public:
    TestShape();
    TestShape(int _id, std::shared_ptr<Material> _matPtr);
    bool operator==(const Shape& other) const override;
    bool operator!=(const Shape& other) const override;
    ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
    std::vector<Intersection> localIntersect(Ray _r) override;
};

#endif
