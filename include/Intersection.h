#ifndef INTERSECTION_H_
#define INTERSECTION_H_
#include <iostream>
#include <vector>

#include "Ray.h"
#include <iostream>
#include <vector>

class Intersection
{
    public:
        Intersection(float _t, int _object);
        float t() const;
        int object() const;
        static std::vector<Intersection> intersections(const Intersection& _i1, const Intersection& _i2);
    private:
        float m_t;
        int m_object;
};

#endif