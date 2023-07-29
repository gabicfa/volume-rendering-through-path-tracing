#include "LambertianBSDF.h"
#include "Utility.h"
#include "Material.h"

LambertianBSDF::LambertianBSDF(const Computation& _comp) 
    : BSDF(_comp) {}

LambertianBSDF::~LambertianBSDF() {}

void LambertianBSDF::evaluateSample(const Computation& _comp, const ngl::Vec3& sampleDirection, ngl::Vec3& L, float &pdf)
{
    auto tempSampleDirection = _comp.normal + randomUnitVector();
    if (near_zero(tempSampleDirection))
        tempSampleDirection = _comp.normal;
    auto albedo = _comp.matPtr->albedo().toVec3();
    L = albedo;
    pdf = 1.0 / (2.0 * M_PI);
}

void LambertianBSDF::generateSample(const Computation& _comp, ngl::Vec3& sampleDirection, ngl::Vec3& L, float& pdf)
{
    if (sampleDirection.dot(_comp.normal.toVec3()) > 0)
    {
        ngl::Vec3 albedo = _comp.matPtr->albedo().toVec3();
        L = albedo / M_PI;
        pdf = 1.0 / (2.0 * M_PI);
    }
    else
    {
        L = ngl::Vec3(0.0, 0.0, 0.0);
        pdf = 0.0;
    }
}
