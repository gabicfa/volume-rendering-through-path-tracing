#ifndef METAL_BSDF_H_
#define METAL_BSDF_H_

#include "BSDF.h"

// MetalBSDF represents a Bidirectional Scatter Distribution Function (BSDF) for metallic surfaces.
// Metallic surfaces tend to reflect rays in a predictable direction determined by the angle of incidence
// and the surface normal, without scattering them in multiple directions like diffuse materials.
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
