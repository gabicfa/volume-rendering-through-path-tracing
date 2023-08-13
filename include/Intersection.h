#ifndef INTERSECTION_H_
#define INTERSECTION_H_
#include <iostream>
#include <vector>
#include <memory>

class Computation;
class Shape;

#include "Ray.h"
class Intersection
{
    public:
        Intersection();
        Intersection(float _t, std::shared_ptr<Shape> _object);
        float t() const;
        std::shared_ptr<Shape> object() const;
        bool operator==(const Intersection& _other) const;
        bool operator!=(const Intersection& _other) const;
        static std::vector<Intersection> intersections(std::vector<Intersection> _intersections);
        static Intersection hit(std::vector<Intersection> _intersections);
        static Intersection nextHitAfter(const Intersection& currentHit, const std::vector<Intersection>& sortedIntersections);
        Computation prepareComputations(Ray _r);
        
    private:
        float m_t = 0;
        std::shared_ptr<Shape> m_object;
};

#endif