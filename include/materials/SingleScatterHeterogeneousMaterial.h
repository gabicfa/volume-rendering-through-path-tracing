#ifndef SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_
#define SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_

#include "Material.h"
#include "bsdfs/IsotropicPhaseBSDF.h"
#include "volumes/SingleScatterHeterogeneousVolume.h"
#include "ngl/Vec3.h"

class SingleScatterHeterogeneousMaterial : public Material
{
public:
    SingleScatterHeterogeneousMaterial(ngl::Vec3 scatteringAlbedo, ngl::Vec3 maxExtinction, int extinction);
    virtual ~SingleScatterHeterogeneousMaterial();

    std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
    bool hasVolume() override;
    std::shared_ptr<Volume> createVolume(Computation& _comp) override;

private:
    const ngl::Vec3 m_scatteringAlbedo;
    const ngl::Vec3 m_maxExtinction;
    const int m_extinctionProperty;
};

#endif
