#ifndef BEERS_LAW_HETEROGENEOUS_MATERIAL_H_
#define BEERS_LAW_HETEROGENEOUS_MATERIAL_H_

#include "Material.h"
#include "bsdfs/TrivialBSDF.h"
#include "volumes/BeersLawHeterogeneousVolume.h"
#include "ngl/Vec3.h"

class BeersLawHeterogeneousMaterial : public Material
{
public:
    BeersLawHeterogeneousMaterial(float maxAbsorption, int absorptionProperty);
    virtual ~BeersLawHeterogeneousMaterial();

    std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
    bool hasVolume() override;
    std::shared_ptr<Volume> createVolume(Computation& _comp) override;
    bool scatter(const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered) const override;

private:
    const float m_maxAbsorption;
    const int m_absorptionProperty;
};

#endif
