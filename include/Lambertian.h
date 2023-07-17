#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "Material.h" 

#include <iostream>
#include <vector>
#include <memory>

class Ray;
class Computation;

class Lambertian : public Material {
    public:
        Lambertian(const ngl::Vec4& _a);
        virtual bool scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const override;

    public:
        ngl::Vec4 m_albedo;
};
#endif