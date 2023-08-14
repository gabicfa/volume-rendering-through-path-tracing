#ifndef METAL_H_
#define METAL_H_

#include "Material.h"
#include "bsdfs/MetalBSDF.h"

// The Metal class represents a specular material.
// This type of material primarily reflects light without internal scattering, described by the MetalBSDF.
class Metal : public Material
{
    public:
        Metal(const ngl::Vec4& _a);
        bool hasVolume() override;
        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        ngl::Vec4 albedo() const override;

    private:
        ngl::Vec4 m_albedo;  // Inherent color of the metallic material.
};

#endif
