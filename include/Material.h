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
        virtual ngl::Vec4 albedo() const { return ngl::Vec4(1.0f, 1.0f, 1.0f, 1.0f); }
};
#endif