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
bool Lambertian::scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const
{
    auto scatterDirection = _comp.normal + randomUnitVector();
    
    if (near_zero(scatterDirection))
        scatterDirection = _comp.normal;

    scattered = Ray(_comp.point, scatterDirection);
    attenuation = m_albedo;
    return true;
}

bool Lambertian::hasAlbedo() const
{
    return true;
}

ngl::Vec4 Lambertian::albedo() const
{
    return m_albedo;
}
