#ifndef DIELECTRIC_BSDF_H_
#define DIELECTRIC_BSDF_H_

#include "BSDF.h"

// The DielectricBSDF class represents a Bidirectional Scattering Distribution Function (BSDF) 
// for dielectric surfaces (such as glass or water). It models the behavior of light as it interacts
// with transparent surfaces that can reflect and refract light.
class DielectricBSDF : public BSDF {
public:
    DielectricBSDF(const Computation& _comp, float ir);
    ~DielectricBSDF();


    void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) override;
    void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) override;

private:
    // The index of refraction for the material. It indicates how much a ray of light is bent or refracted when entering the material.
    float m_ir;

    // The computation object storing the details of light-surface interaction.
    Computation m_comp;
    
    // A helper method that computes the reflectance probability using Schlick's approximation.
    // It's used to determine the likelihood of reflection vs. refraction at an interface.
    static double reflectance(double cosine, double ref_idx);
};

#endif
