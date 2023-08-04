#ifndef DIELECTRIC_H_
#define DIELECTRIC_H_

#include "Material.h"
#include "bsdfs/DielectricBSDF.h"

class Dielectric : public Material {
public:
    Dielectric(float index_of_refraction);
    bool hasVolume() override;
    std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
    bool scatter(
        const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
    ) const override;

private:
    float m_ir;
};

#endif
