#ifndef ABSMATERIAL_H_
#define ABSMATERIAL_H_
#include <iostream>

class Computation;
#include "Ray.h"

class AbsMaterial
{
    public:
        virtual bool scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const = 0;
};
#endif