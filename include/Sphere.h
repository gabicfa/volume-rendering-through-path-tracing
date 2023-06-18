#ifndef SPHERE_H_
#define SPHERE_H_

#include <vector>
#include <ngl/Mat4.h>
class Shape;
#include "Shape.h"
#include "Ray.h"

class Intersection;
#include "Intersection.h"

class Sphere : public Shape
{
    public:
        Sphere();
        Sphere(int _id);
        int id() const override;
        bool operator==(const Shape& other) const override;
        bool operator!=(const Shape& other) const override;
        ngl::Mat4 transform() const override;
        void setTransform(const ngl::Mat4& _tMatrix) override;
        ngl::Vec4 normalAt(ngl::Vec4 _worldPoint) override;
        Material material() const override;
        void setMaterial(const Material& _m) override;
        std::vector<Intersection> intersect(Ray _r) override;
    private:
        int m_id = 0;
        ngl::Mat4 m_transform = ngl::Mat4();
        Material m_material = Material();
        std::vector<Intersection> localIntersect(Ray _r);
        ngl::Vec4 localNormalAt(ngl::Vec4 _localPoint);;

};

#endif
