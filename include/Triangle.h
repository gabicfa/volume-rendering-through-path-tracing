#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Shape.h"

class Ray;
class Intersection;
class Material;

// The Triangle class provides functionality for representing a 3D triangle in space.
// It is an implementation of the abstract Shape class.
class Triangle : public Shape
{
public:
    Triangle(const ngl::Vec4& p1, const ngl::Vec4& p2, const ngl::Vec4& p3);
    Triangle(const ngl::Vec4& p1, const ngl::Vec4& p2, const ngl::Vec4& p3,  std::shared_ptr<Material> _matPtr);

    // Getter functions to retrieve triangle vertices and its computed edges and normal.
    const ngl::Vec4& getP1() const;
    const ngl::Vec4& getP2() const;
    const ngl::Vec4& getP3() const;
    const ngl::Vec4& getE1() const;
    const ngl::Vec4& getE2() const;
    const ngl::Vec4& getNormal() const;

    bool operator==(const Shape& other) const override;
    bool operator!=(const Shape& other) const override;
    ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
    std::vector<Intersection> localIntersect(Ray _r) override;        

private:
    // Triangle vertices.
    ngl::Vec4 m_p1;
    ngl::Vec4 m_p2;
    ngl::Vec4 m_p3;
    
    // Edge vectors derived from vertices.
    ngl::Vec4 m_e1;
    ngl::Vec4 m_e2;
    
    // Normal vector for the triangle surface.
    ngl::Vec4 m_normal;
};

#endif
