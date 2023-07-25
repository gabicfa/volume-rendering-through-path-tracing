#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <iostream>

class Volume;
class Computation;
#include "Ray.h"
#include "BSDF.h"

class Material
{
    public:
        virtual std::shared_ptr<BSDF> createBSDF(const Computation& _comp) = 0;
        virtual bool hasVolume() = 0;
        virtual std::shared_ptr<Volume> createVolume(Computation &_comp)
        {
            return nullptr;
        }

        virtual bool scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const = 0;
        virtual ngl::Vec4 albedo() const = 0;
};
#endif