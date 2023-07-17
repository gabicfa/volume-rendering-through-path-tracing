#ifndef METAL_H_
#define METAL_H_

#include "Material.h"

#include <iostream>
#include <vector>
#include <memory>

class Ray;
class Computation;
class Material;

class Metal : public Material {
    public:
        Metal(const ngl::Vec4& _a);
        virtual bool scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const override;

    public:
        ngl::Vec4 m_albedo;
};
#endif