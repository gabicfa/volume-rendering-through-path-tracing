#ifndef LIGHT_EMITTING_H_
#define LIGHT_EMITTING_H_

#include "Material.h"
#include "bsdfs/LightEmittingBSDF.h"

// The LightEmitting class represents a light-emitting material.
// This type of material is designed to represent emitting light objects
class LightEmitting : public Material
{
    public:
        LightEmitting(const ngl::Vec4& _a);
        bool hasVolume() override;
        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        ngl::Vec4 albedo() const override;

    private:
        ngl::Vec4 m_emitColor;  // The color the material emits.
};

#endif
