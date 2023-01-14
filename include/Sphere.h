#ifndef SPHERE_H_
#define SPHERE_H_
#include <iostream>
#include <vector>
#include <ngl/Mat4.h>

#include "Ray.h"
#include "Intersection.h"

class Sphere
{
    public:
        Sphere(int _id);
        std::vector<Intersection> intersect(Ray _r);
        int id() const;
        bool operator==(const Sphere& other) const;
        ngl::Mat4 transform() const;
        void setTransform(ngl::Mat4 _tMatrix);
    private:
        int m_id;
        ngl::Mat4 m_transform = ngl::Mat4();
};

#endif