#ifndef LAMBERTIAN_BSDF_H_
#define LAMBERTIAN_BSDF_H_

#include "BSDF.h"

class LambertianBSDF : public BSDF
{
    public:
        LambertianBSDF(const Computation& _comp);
        ~LambertianBSDF();

        void evaluateSample(const Computation& _comp, const ngl::Vec3& sampleDirection, ngl::Vec3& L, float &pdf) override;
        void generateSample(const Computation& _comp, ngl::Vec3& sampleDirection, ngl::Vec3& L, float& pdf) override;

    private:
        Computation m_comp;
};

#endif