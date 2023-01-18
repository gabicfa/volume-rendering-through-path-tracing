#ifndef COMPUTATION_H_
#define COMPUTATION_H_
#include <iostream>

#include <ngl/Vec4.h>
#include "Sphere.h"

class Sphere;

class Computation
{
    public:
        Computation() = default;
        float t;
        Sphere *object;
        ngl::Vec4 point;
        ngl::Vec4 eye;
        ngl::Vec4 normal;
        bool inside;
}; 

#endif