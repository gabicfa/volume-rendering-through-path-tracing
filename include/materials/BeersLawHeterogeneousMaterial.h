#ifndef BEERS_LAW_HETEROGENEOUS_MATERIAL_H_
#define BEERS_LAW_HETEROGENEOUS_MATERIAL_H_

#include "Material.h"
#include "bsdfs/TrivialBSDF.h"
#include "volumes/BeersLawHeterogeneousVolume.h"
#include "ngl/Vec3.h"

// The BeersLawHeterogeneousMaterial class represents a material governed by Beer's Law 
// in a heterogeneous medium. In contrast to a homogenous medium where properties are 
// consistent throughout, a heterogeneous medium has properties that vary at different 
// points. This material models the attenuation of light based on spatially varying properties.
class BeersLawHeterogeneousMaterial : public Material
{
    public:
        BeersLawHeterogeneousMaterial(float maxAbsorption);
        virtual ~BeersLawHeterogeneousMaterial();

        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        bool hasVolume() override;
        std::shared_ptr<Volume> createVolume(Computation& _comp) override;

    private:
        const float m_maxAbsorption;           // The maximum absorption coefficient for the material.
};

#endif
