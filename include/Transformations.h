#ifndef TRANSFORMATIONS_H_
#define TRANSFORMATIONS_H_
#include <iostream>

#include<ngl/Vec4.h>
#include<ngl/Mat4.h>

class Transformations
{
    public:
        static ngl::Mat4 viewTransform(const ngl::Vec4& from, const ngl::Vec4& to, const ngl::Vec4& up);
};

#endif