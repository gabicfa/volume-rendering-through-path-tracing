#ifndef VOLUME_H_
#define VOLUME_H_
#include <iostream>

#include<ngl/Vec3.h>
#include<ngl/Vec4.h>
#include "Computation.h"
#include "Ray.h"
#include "Shape.h"

class Volume
{
    public:
        Volume(Computation &comp) : m_comp(comp) {}
        virtual ~Volume() {}
        virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
            &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s) = 0;
        virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) = 0;
    protected:
        Computation &m_comp;
};

#endif