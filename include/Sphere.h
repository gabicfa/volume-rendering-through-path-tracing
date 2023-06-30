#ifndef SPHERE_H_
#define SPHERE_H_

#include <vector>
#include <ngl/Mat4.h>
#include "Shape.h"

class Ray;
class AbsMaterial;
class Intersection;

class Sphere : public Shape
{
    public:
        Sphere();
        Sphere(int _id);
        Sphere(int _id, std::shared_ptr<AbsMaterial> _matPtr);
        bool operator==(const Shape& other) const override;
        bool operator!=(const Shape& other) const override;
        ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
        std::vector<Intersection> localIntersect(Ray _r) override;
};

#endif
