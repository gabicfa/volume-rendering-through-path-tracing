#include "Lambertian.h"
#include "Utility.h"
#include "Ray.h"
#include "Computation.h"

Lambertian::Lambertian(const ngl::Vec4& _a)
{
    m_albedo = _a;
}

bool Lambertian::scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const
{
    auto scatterDirection = _comp.normal + randomUnitVector();
    
    // Catch degenerate scatter direction
    if (near_zero(scatterDirection))
        scatterDirection = _comp.normal;

    scattered = Ray(_comp.point, scatterDirection);
    attenuation = m_albedo;
    return true;
}