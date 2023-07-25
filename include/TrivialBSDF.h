#ifndef TRIVIAL_BSDF_H
#define TRIVIAL_BSDF_H

#include "BSDF.h"
#include "Computation.h"
#include "ngl/Vec3.h"

class TrivialBSDF : public BSDF {
public:
    TrivialBSDF(const Computation& comp);
    virtual ~TrivialBSDF();

    virtual void evaluateSample(const Computation& _comp, const ngl::Vec3& sampleDirection, ngl::Vec3& L, float &pdf) override;
    virtual void generateSample(const Computation& _comp, ngl::Vec3& sampleDirection, ngl::Vec3& L, float& pdf) override;
};

#endif
