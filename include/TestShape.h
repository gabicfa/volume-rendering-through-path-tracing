#ifndef TESTSHAPE_H_
#define TESTSHAPE_H_

#include "Shape.h"

class TestShape : public Shape
{
public:
    TestShape();

    int id() const override;
    ngl::Mat4 transform() const override;
    void setTransform(const ngl::Mat4& _tMatrix) override;
    Material material() const override;
    void setMaterial(const Material& _m) override;
    std::vector<Intersection> intersect(Ray _r) override;
    ngl::Vec4 normalAt(ngl::Vec4 _worldPoint) override;
    bool operator==(const Shape& other) const override;
    bool operator!=(const Shape& other) const override;
};

#endif
