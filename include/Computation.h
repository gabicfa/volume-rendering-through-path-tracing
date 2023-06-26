#ifndef COMPUTATION_H_
#define COMPUTATION_H_

#include <iostream>
#include <ngl/Vec4.h>

class AbsMaterial;
class Shape;

class Computation
{
    public:
        Computation() = default;
        float t;
        std::shared_ptr<Shape> object;
        std::shared_ptr<AbsMaterial> matPtr;
        ngl::Vec4 point;
        ngl::Vec4 eye;
        ngl::Vec4 normal;
        
        bool inside;
}; 

#endif