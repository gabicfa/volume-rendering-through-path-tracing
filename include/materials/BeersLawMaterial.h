#ifndef BEERS_LAW_MATERIAL_H_
#define BEERS_LAW_MATERIAL_H_

#include "Material.h"
#include "bsdfs/TrivialBSDF.h"
#include "volumes/BeersLawVolume.h"
#include "ngl/Vec3.h"

// The BeersLawMaterial class represents a material governed by Beer's Law.
// It models the attenuation of light as it passes through a volume, decreasing its intensity based on the medium's properties.
// This is commonly used for effects like colored glass or translucent fluids where light can pass through but gets absorbed to some degree.
class BeersLawMaterial : public Material
{
    public:
        BeersLawMaterial(const ngl::Vec3& extinction);
        virtual ~BeersLawMaterial();

        std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
        bool hasVolume() override;
        std::shared_ptr<Volume> createVolume(Computation& _comp) override;

    private:
        const ngl::Vec3 m_extinction;  // The coefficient of light extinction (absorption) as it travels through the material.
};

#endif
