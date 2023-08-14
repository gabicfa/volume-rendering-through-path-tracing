#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "Material.h"
#include "bsdfs/LambertianBSDF.h"

// The Lambertian class represents a Lambertian (diffuse) material.
// This type of material scatters light uniformly in all directions, regardless of the incoming light direction.
class Lambertian : public Material
{
    public:
        Lambertian(const ngl::Vec4& _a);
        bool hasVolume() override;
        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        ngl::Vec4 albedo() const override;

    private:
        ngl::Vec4 m_albedo;  // The albedo (color) of the Lambertian material.
};

#endif
