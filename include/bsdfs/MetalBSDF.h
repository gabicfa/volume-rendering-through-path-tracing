#ifndef METAL_BSDF_H_
#define METAL_BSDF_H_

#include "BSDF.h"

class MetalBSDF : public BSDF
{
    public:
        MetalBSDF(const Computation& _comp);
        ~MetalBSDF();

        void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) override;
        void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) override;

    private:
        Computation m_comp;

};

#endif
