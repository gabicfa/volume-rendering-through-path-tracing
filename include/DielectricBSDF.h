#ifndef DIELECTRIC_BSDF_H_
#define DIELECTRIC_BSDF_H_

#include "BSDF.h"

class DielectricBSDF : public BSDF {
public:
    DielectricBSDF(const Computation& _comp, float ir);
    ~DielectricBSDF();

    void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) override;
    void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) override;

private:
    float m_ir;
    Computation m_comp;
    static double reflectance(double cosine, double ref_idx);
};

#endif
