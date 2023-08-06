#ifndef BEERS_LAW_MATERIAL_H_
#define BEERS_LAW_MATERIAL_H_

#include "Material.h"
#include "bsdfs/TrivialBSDF.h"
#include "volumes/BeersLawVolume.h"
#include "ngl/Vec3.h"

class BeersLawMaterial : public Material
{
public:
    BeersLawMaterial(const ngl::Vec3& extinction);
    virtual ~BeersLawMaterial();

    std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
    bool hasVolume() override;
    std::shared_ptr<Volume> createVolume(Computation& _comp) override;

private:
    const ngl::Vec3 m_extinction;
};

#endif
