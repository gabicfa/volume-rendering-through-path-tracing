#ifndef COMPUTATION_H_
#define COMPUTATION_H_

#include <iostream>
#include <ngl/Vec4.h>
#include "Ray.h"

class Material;
class Shape;
class Ray;

// The Computation class captures various values computed at an intersection point.
// These values can be used for shading and other computations.
class Computation
{
public:
    Computation() = default;

    float t;                             // The t-value of the intersection.
    std::shared_ptr<Shape> object;       // The intersected object.
    std::shared_ptr<Material> matPtr;    // Material of the intersected object.
    ngl::Vec4 point;                     // Point of intersection.
    ngl::Vec4 eye;                       // Direction vector from the intersection point to the eye.
    ngl::Vec4 normal;                    // Normal vector at the intersection point.
    Ray incomingRay;                     // The ray causing the intersection.
    bool inside;                         // Flag to check if the intersection is inside an object.

    // Recompute values (like normal) based on the direction of the incoming ray.
    void recompute();

}; 

#endif