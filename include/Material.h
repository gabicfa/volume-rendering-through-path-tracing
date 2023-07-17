#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <iostream>

class Computation;
#include "Ray.h"

class Material
{
    public:
        virtual bool scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const = 0;
};
#endif