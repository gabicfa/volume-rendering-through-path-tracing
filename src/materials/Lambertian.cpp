#include "materials/Lambertian.h"
#include "Utility.h"
#include "Ray.h"
#include "Computation.h"

Lambertian::Lambertian(const ngl::Vec4& _a)
{
    m_albedo = _a;
}

bool Lambertian::hasVolume()
{
    return false;
}
std::shared_ptr<BSDF> Lambertian::createBSDF(const Computation& _comp)
{
    return std::make_shared<LambertianBSDF>(_comp);
}

ngl::Vec4 Lambertian::albedo() const
{
    return m_albedo;
}
