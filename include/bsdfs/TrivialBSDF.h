#ifndef TRIVIAL_BSDF_H
#define TRIVIAL_BSDF_H

#include "BSDF.h"
#include "Computation.h"
#include "ngl/Vec3.h"

// The TrivialBSDF class represents a Bidirectional Scattering Distribution Function (BSDF)
// for surfaces that don't possess any distinct reflection or refraction properties. 
// Instead, for indirect rays, it continues the ray in the outgoing direction. 
// This makes it ideal for representing a volumetric region which absorbs light with no surface properties.
class TrivialBSDF : public BSDF {
public:
    TrivialBSDF(const Computation& comp);
    virtual ~TrivialBSDF();

    virtual void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) override;
    virtual void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) override;
};

#endif
