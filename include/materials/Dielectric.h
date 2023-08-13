#ifndef DIELECTRIC_H_
#define DIELECTRIC_H_

#include "Material.h"
#include "bsdfs/DielectricBSDF.h"

// The Dielectric class represents a dielectric (transparent) material, such as glass.
// This type of material has unique properties in terms of how it reflects and refracts light, 
// characterized by its index of refraction.
class Dielectric : public Material {
    public:
        Dielectric(float index_of_refraction);
        bool hasVolume() override;
        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;

    private:
        float m_ir;  // Index of refraction for the dielectric material.
};

#endif
