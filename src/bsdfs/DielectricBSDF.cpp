#include "bsdfs/DielectricBSDF.h"
#include "Utility.h"

DielectricBSDF::DielectricBSDF(const Computation& _comp, float ir)
    : BSDF(_comp), m_ir(ir) {}

DielectricBSDF::~DielectricBSDF() {}

void DielectricBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    float refraction_ratio = _comp.inside ? (1.0 / m_ir) : m_ir;
    ngl::Vec3 unit_direction = unitVector(_comp.incomingRay.direction()).toVec3();
    float cos_theta = fmin((-unit_direction).dot(_comp.normal.toVec3()), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    ngl::Vec3 direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomDouble(0,1))
        direction = unit_direction.reflect(_comp.normal.toVec3());
    else
        direction = refract(unit_direction, _comp.normal.toVec3(), refraction_ratio);

    sampleDirection = direction;
    L = ngl::Vec3(1.0, 1.0, 1.0); // assuming full white as the light color
    pdf = 1.0; // considering uniform sampling
}

void DielectricBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    float refraction_ratio = _comp.inside ? (1.0 / m_ir) : m_ir;
    ngl::Vec3 unit_direction = unitVector(_comp.incomingRay.direction()).toVec3();
    float cos_theta = fmin((-unit_direction).dot(_comp.normal.toVec3()), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    ngl::Vec3 expectedDirection;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomDouble(0,1))
        expectedDirection = unit_direction.reflect(_comp.normal.toVec3());
    else
        expectedDirection = refract(unit_direction, _comp.normal.toVec3(), refraction_ratio);

    if (expectedDirection == sampleDirection.toVec3()) {
        L = ngl::Vec3(1.0, 1.0, 1.0); // assuming full white as the light color
        pdf = 1.0; // considering uniform sampling
    } else {
        L = ngl::Vec3(0.0, 0.0, 0.0);
        pdf = 0.0;
    }
}

double DielectricBSDF::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}

