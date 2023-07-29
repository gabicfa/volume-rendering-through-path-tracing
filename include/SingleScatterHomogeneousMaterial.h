#ifndef SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_
#define SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_

#include "Material.h"
#include "IsotropicPhaseBSDF.h"
#include "SingleScatterHomogeneousVolume.h"
#include "ngl/Vec3.h"

class SingleScatterHomogeneousMaterial : public Material
{
public:
    SingleScatterHomogeneousMaterial(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction);
    virtual ~SingleScatterHomogeneousMaterial();

    std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
    bool hasVolume() override;
    std::shared_ptr<Volume> createVolume(Computation& _comp) override;
    bool scatter(const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered) const override;

private:
    const ngl::Vec3 m_scatteringAlbedo;
    const ngl::Vec3 m_extinction;
};

#endif
