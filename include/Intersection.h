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
        Intersection() = default;
        Intersection(float _t, int _object);
        float t() const;
        int object() const;
        bool operator==(const Intersection& other) const;
        static std::vector<Intersection> intersections(std::vector<Intersection> intersections);
        static Intersection hit(std::vector<Intersection> intersections);
    private:
        float m_t;
        int m_object;
};

#endif