#ifndef SPHERE_H_
#define SPHERE_H_

#include <vector>
#include <ngl/Mat4.h>
#include "Shape.h"
#include "Ray.h"

class Sphere : public Shape
{
    public:
        Sphere();
        Sphere(int _id);
        bool operator==(const Shape& other) const override;
        bool operator!=(const Shape& other) const override;
        ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
        std::vector<Intersection> localIntersect(Ray _r) override;

        ngl::Vec4 unitVector(const ngl::Vec4& vec);
        ngl::Vec4 randomUnitVector();
        ngl::Vec4 randomInUnitSphere();
        ngl::Vec4 randomInHemisphere(const ngl::Vec4& _normal);

};

#endif
