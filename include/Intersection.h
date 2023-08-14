#ifndef INTERSECTION_H_
#define INTERSECTION_H_

#include <iostream>
#include <vector>
#include <memory>

class Computation;
class Shape;

#include "Ray.h"

// The Intersection class represents the point where a ray intersects an object in the scene.
class Intersection
{
    public:
        Intersection();
        Intersection(float _t, std::shared_ptr<Shape> _object);
        float t() const;
        std::shared_ptr<Shape> object() const;

        bool operator==(const Intersection& _other) const;
        bool operator!=(const Intersection& _other) const;

        // Sort a vector of intersections based on their t-values.
        static std::vector<Intersection> intersections(std::vector<Intersection> _intersections);
        // Find the closest valid intersection point.
        static Intersection hit(std::vector<Intersection> _intersections);
        // Find the next intersection after a given one.
        static Intersection nextHitAfter(const Intersection& currentHit, const std::vector<Intersection>& sortedIntersections);
        
        // Compute useful values at the intersection point.
        Computation prepareComputations(Ray _r);
        
    private:
        // t-value of the intersection.
        float m_t;
        // Object being intersected.
        std::shared_ptr<Shape> m_object;
};
#endif