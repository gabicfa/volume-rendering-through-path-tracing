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
        int id() const override;
        bool operator==(const Shape& other) const override;
        bool operator!=(const Shape& other) const override;
        std::vector<Intersection> intersect(Ray _r) override;
        ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint) override;
    private:
        int m_id = 0;
        std::vector<Intersection> localIntersect(Ray _r);
};

#endif
