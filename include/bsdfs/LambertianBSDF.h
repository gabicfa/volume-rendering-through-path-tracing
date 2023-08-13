#ifndef LAMBERTIAN_BSDF_H_
#define LAMBERTIAN_BSDF_H_

#include "BSDF.h"

// LambertianBSDF represents a Lambertian Bidirectional Scatter Distribution Function (BSDF).
// Lambertian reflection is perfectly diffused reflection, meaning when light hits the surface,
// it has an equal chance of reflecting in any direction in the hemisphere around the normal.
class LambertianBSDF : public BSDF
{
    public:
        LambertianBSDF(const Computation& _comp);
        ~LambertianBSDF();

        void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) override;
        void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) override;

    private:
        Computation m_comp;
};

#endif