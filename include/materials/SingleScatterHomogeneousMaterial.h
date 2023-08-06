#ifndef SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_
#define SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_

#include "Material.h"
#include "bsdfs/IsotropicPhaseBSDF.h"
#include "volumes/SingleScatterHomogeneousVolume.h"
#include "ngl/Vec3.h"

class SingleScatterHomogeneousMaterial : public Material
{
public:
    SingleScatterHomogeneousMaterial(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction);
    virtual ~SingleScatterHomogeneousMaterial();

    std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
    bool hasVolume() override;
    std::shared_ptr<Volume> createVolume(Computation& _comp) override;

private:
    const ngl::Vec3 m_scatteringAlbedo;
    const ngl::Vec3 m_extinction;
};

#endif
