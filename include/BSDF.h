#ifndef BSDF_H_
#define BSDF_H_

#include "Computation.h"

class BSDF {
    public:
        BSDF(const Computation &comp) : m_comp(comp) {}
        virtual ~BSDF() {}

        virtual void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) = 0;
        virtual void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) = 0;

    protected:
        const Computation &m_comp;
};

#endif