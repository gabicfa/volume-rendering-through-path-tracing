#ifndef SPHERE_H_
#define SPHERE_H_
#include <iostream>
#include <vector>

#include "Ray.h"
#include "Intersection.h"

class Sphere
{
    public:
        Sphere(int _id);
        std::vector<Intersection> intersect(Ray _r);
        int id() const;
        bool operator==(const Sphere& other) const;
    private:
        int m_id;
};

#endif