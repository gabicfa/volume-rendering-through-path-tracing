#ifndef ISOTROPIC_PHASE_BSDF_H
#define ISOTROPIC_PHASE_BSDF_H

#include "BSDF.h"
#include "Computation.h"
#include "ngl/Vec3.h"

// The IsotropicPhaseBSDF class represents an isotropic phase function. 
// It models the scattering properties of media where 
// the scattering is uniform in all directions, regardless of the incident direction.
class IsotropicPhaseBSDF : public BSDF {
public:
    IsotropicPhaseBSDF(const Computation& comp);
    virtual ~IsotropicPhaseBSDF();

    virtual void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) override;
    virtual void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) override;
};

#endif
