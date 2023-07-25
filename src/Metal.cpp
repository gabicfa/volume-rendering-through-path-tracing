#include "Metal.h"
#include "Utility.h"
#include "Ray.h"
#include "Computation.h"

Metal::Metal(const ngl::Vec4& _a)
{
    m_albedo = _a;
}

bool Metal::hasVolume()
{
    return false;
}

std::shared_ptr<BSDF> Metal::createBSDF(const Computation& _comp)
{
    return std::make_shared<MetalBSDF>(_comp);
}

bool Metal::scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const
{
    ngl::Vec3 reflected = unitVector(_rIn.direction()).toVec3().reflect(_comp.normal.toVec3());
    scattered = Ray(_comp.point, reflected);
    attenuation = m_albedo;
    return (scattered.direction().dot(_comp.normal) > 0);
}

ngl::Vec4 Metal::albedo() const
{
    return m_albedo;
}
