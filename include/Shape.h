#ifndef SHAPE_H_
#define SHAPE_H_

#include <vector>
#include <ngl/Vec4.h>
#include "Material.h"
#include "Ray.h"

class Intersection;
#include "Intersection.h"

class Shape
{
    public:
        virtual ~Shape() = default;
        virtual int id() const = 0;
        virtual ngl::Mat4 transform() const = 0;
        virtual void setTransform(const ngl::Mat4& _tMatrix) = 0;
        virtual Material material() const = 0;
        virtual void setMaterial(const Material& _m) = 0;

        virtual bool operator==(const Shape& other) const = 0;
        virtual bool operator!=(const Shape& other) const = 0;

        virtual std::vector<Intersection> intersect(Ray _r) = 0;
        virtual ngl::Vec4 normalAt(ngl::Vec4 _worldPoint) = 0;
};

#endif
