#ifndef COMPUTATION_H_
#define COMPUTATION_H_

#include <iostream>
#include <ngl/Vec4.h>
#include "Ray.h"

class Material;
class Shape;
class Ray;

class Computation
{
    public:
        Computation() = default;
        float t;
        std::shared_ptr<Shape> object;
        std::shared_ptr<Material> matPtr;
        ngl::Vec4 point;
        ngl::Vec4 eye;
        ngl::Vec4 normal;
        Ray incomingRay;
        bool inside;
        void recompute(const ngl::Vec4 &newPoint, ngl::Vec4 dir);

}; 

#endif