#ifndef COMPUTATION_H_
#define COMPUTATION_H_
#include <iostream>

#include <ngl/Vec4.h>
#include "Shape.h"

class Shape;

class Computation
{
    public:
        Computation() = default;
        float t;
        std::shared_ptr<Shape> object;
        ngl::Vec4 point;
        ngl::Vec4 eye;
        ngl::Vec4 normal;
        bool inside;
}; 

#endif