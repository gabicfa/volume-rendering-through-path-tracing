#ifndef SPHERE_H_
#define SPHERE_H_
#include <iostream>
#include <vector>
#include <ngl/Mat4.h>

#include "Ray.h"
#include "Material.h"
class Intersection;
#include "Intersection.h"
class Sphere
{
    public:
        Sphere();
        Sphere(int _id);
        std::vector<Intersection> intersect(Ray _r);
        int id() const;
        bool operator==(const Sphere& other) const;
        bool operator!=(const Sphere& other) const;
        ngl::Mat4 transform() const;
        void setTransform(ngl::Mat4 _tMatrix);
        ngl::Vec4 normalAt(ngl::Vec4 _worldPoint);
        Material material() const;
        void material(Material _m);
    private:
        int m_id = 0;
        ngl::Mat4 m_transform = ngl::Mat4();
        Material m_material = Material();

};

#endif