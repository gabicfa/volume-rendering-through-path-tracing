#ifndef METAL_H_
#define METAL_H_

#include "Material.h"
#include "bsdfs/MetalBSDF.h"

class Metal : public Material
{
    public:
        Metal(const ngl::Vec4& _a);
        bool hasVolume() override;
        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        ngl::Vec4 albedo() const override;

    private:
        ngl::Vec4 m_albedo;
};

#endif
