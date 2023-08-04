#ifndef LIGHT_EMITTING_BSDF_H_
#define LIGHT_EMITTING_BSDF_H_

#include "BSDF.h"

class LightEmittingBSDF : public BSDF
{
    public:
        LightEmittingBSDF(const Computation& _comp);
        ~LightEmittingBSDF();

        void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) override;
        void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) override;

    private:
        Computation m_comp;
};

#endif
