#ifndef LAMBERTIAN_H_
#define LAMBERTIAN_H_

#include "Material.h"
#include "LambertianBSDF.h"

class Lambertian : public Material
{
    public:
        Lambertian(const ngl::Vec4& _a);
        bool hasVolume() override;
        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        bool scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const override;
        ngl::Vec4 albedo() const override;

    private:
        ngl::Vec4 m_albedo;
};

#endif
