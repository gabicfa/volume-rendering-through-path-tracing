#ifndef INTERSECTION_H_
#define INTERSECTION_H_
#include <iostream>
#include <vector>

#include "Ray.h"
#include <iostream>
#include <vector>
#include "Computation.h"

class Sphere;

class Intersection
{
    public:
        Intersection();
        Intersection(float _t, std::shared_ptr<Sphere> _object);
        float t() const;
        std::shared_ptr<Sphere> object() const;
        bool operator==(const Intersection& other) const;
        bool operator!=(const Intersection& other) const;
        static std::vector<Intersection> intersections(std::vector<Intersection> intersections);
        static Intersection hit(std::vector<Intersection> intersections);
        Computation prepareComputations(Ray _r);
    private:
        float m_t = 0;
        std::shared_ptr<Sphere> m_object;
};

#endif