#ifndef METAL_H_
#define METAL_H_

#include "Material.h"
#include "MetalBSDF.h"

class Metal : public Material
{
    public:
        Metal(const ngl::Vec4& _a);
        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        bool scatter(
                const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
                ) const override;
        ngl::Vec4 albedo() const override;

    private:
        ngl::Vec4 m_albedo;
};

#endif
