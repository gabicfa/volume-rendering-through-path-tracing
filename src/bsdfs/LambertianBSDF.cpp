#include "bsdfs/LambertianBSDF.h"
#include "Utility.h"
#include "Material.h"

LambertianBSDF::LambertianBSDF(const Computation& _comp) 
    : BSDF(_comp) {}

LambertianBSDF::~LambertianBSDF() {}

// Computes the reflected light intensity (L) for a given sample direction using Lambertian BRDF.
// If the light is coming from behind the surface, no light is reflected. Otherwise, it evaluates 
// the BRDF and computes the probability density function (pdf).
void LambertianBSDF::evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf)
{
    // The Lambertian BRDF is 1/pi * cos(theta), where theta is the angle between
    // the sample direction and the normal.
    float cosTheta = _comp.normal.dot(sampleDirection);
    if (cosTheta < 0) 
    {
        // Light is coming from behind the surface, so no light is reflected.
        L = ngl::Vec3(0, 0, 0);
        pdf = 0;
    } 
    else 
    {
        L = _comp.matPtr->albedo().toVec3() / M_PI * cosTheta;
        pdf = cosTheta / M_PI;  // PDF for cosine distribution.
    }
}

// Randomly generates a direction in the hemisphere around the normal based on Lambertian reflection.
// After obtaining the sample direction, it computes the reflected light intensity (L) and its 
// associated probability density function (pdf) using the Lambertian BRDF.
void LambertianBSDF::generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf)
{
    // For Lambertian reflection, just pick a random direction in the hemisphere
    // around the normal. The direction is given by spherical coordinates (phi, theta) where
    // phi is a random angle around the normal and theta is an angle from the normal given by
    // cos(theta) = sqrt(1 - u) for a random u in [0, 1].
    float u = randomFloat();
    float v = randomFloat();
    float phi = 2 * M_PI * u;
    float theta = acos(sqrt(1 - v));

    // Convert from spherical to Cartesian coordinates.
    sampleDirection = ngl::Vec3(
        sin(theta) * cos(phi),
        cos(theta),
        sin(theta) * sin(phi)
    );

    // Rotate the sample direction so it's in the hemisphere around the normal.
    ngl::Vec3 up = abs(_comp.normal.m_y) < 0.99f ? ngl::Vec3(0, 1, 0) : ngl::Vec3(1, 0, 0);
    ngl::Vec3 tangent = _comp.normal.toVec3().cross(up);
    tangent.normalize();
    ngl::Vec3 bitangent = _comp.normal.toVec3().cross(tangent);
    sampleDirection = (tangent * sampleDirection.m_x) + _comp.normal.toVec3() * sampleDirection.m_y + bitangent * sampleDirection.m_z;

    // The Lambertian BRDF and the PDF are the same as in evaluateSample.
    evaluateSample(_comp, sampleDirection, L, pdf);
}