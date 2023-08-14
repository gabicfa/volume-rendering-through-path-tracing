#include "bsdfs/DielectricBSDF.h"
#include "Utility.h"

// Constructor initializes the DielectricBSDF with a given computation and index of refraction.
DielectricBSDF::DielectricBSDF(const Computation& _comp, float ir)
    : BSDF(_comp), m_ir(ir) {}

DielectricBSDF::~DielectricBSDF() {}

// Generates a sample direction for light traveling through or reflecting off the dielectric surface.
void DielectricBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    // Determine the refraction ratio based on whether the ray is inside the object.
    float refraction_ratio = _comp.inside ? (1.0 / m_ir) : m_ir;

    // Calculate the cosine and sine of the angle between the incoming ray direction and the normal.
    ngl::Vec3 unit_direction = unitVector(_comp.incomingRay.direction()).toVec3();
    float cos_theta = fmin((-unit_direction).dot(_comp.normal.toVec3()), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    // Determine whether total internal reflection occurs.
    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    ngl::Vec3 direction;

    // Check conditions for reflection vs refraction, and compute the corresponding direction.
    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomFloat(0,1))
        direction = unit_direction.reflect(_comp.normal.toVec3());
    else
        direction = refract(unit_direction, _comp.normal.toVec3(), refraction_ratio);

    sampleDirection = direction;

    // Assign constant light intensity and probability for dielectric reflection/refraction.
    L = ngl::Vec3(1.0, 1.0, 1.0);
    pdf = 1.0;
}

// Evaluates the reflection or refraction of the dielectric surface for a given sample direction. 
void DielectricBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    // (The logic is similar to generateSample but focused on verifying the sample direction.)
    
    float refraction_ratio = _comp.inside ? (1.0 / m_ir) : m_ir;
    ngl::Vec3 unit_direction = unitVector(_comp.incomingRay.direction()).toVec3();
    float cos_theta = fmin((-unit_direction).dot(_comp.normal.toVec3()), 1.0);
    float sin_theta = sqrt(1.0 - cos_theta * cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    ngl::Vec3 expectedDirection;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > randomFloat(0,1))
        expectedDirection = unit_direction.reflect(_comp.normal.toVec3());
    else
        expectedDirection = refract(unit_direction, _comp.normal.toVec3(), refraction_ratio);

    // If the provided sample direction matches the expected direction, assign light intensity and probability.
    if (expectedDirection == sampleDirection.toVec3()) 
    {
        L = ngl::Vec3(1.0, 1.0, 1.0); 
        pdf = 1.0;
    } 
    else 
    {
        L = ngl::Vec3(0.0, 0.0, 0.0);
        pdf = 0.0;
    }
}

// Computes the reflectance probability using Schlick's approximation.
double DielectricBSDF::reflectance(double cosine, double ref_idx) {
    // Use Schlick's approximation for reflectance to account for varying reflectivity at different angles.
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0)*pow((1 - cosine),5);
}
