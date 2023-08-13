#include "materials/Lambertian.h"
#include "Utility.h"
#include "Ray.h"
#include "Computation.h"

Lambertian::Lambertian(const ngl::Vec4& _a) : m_albedo(_a) {}

// The Lambertian material does not have a volumetric component.
bool Lambertian::hasVolume()
{
    return false;
}

// Creates a Lambertian BSDF instance for this material.
std::shared_ptr<BSDF> Lambertian::createBSDF(const Computation& _comp)
{
    return std::make_shared<LambertianBSDF>(_comp);
}

ngl::Vec4 Lambertian::albedo() const
{
    return m_albedo;
}
