#include "materials/LightEmitting.h"

LightEmitting::LightEmitting(const ngl::Vec4& _a)
{
    m_emitColor = _a;
}

bool LightEmitting::hasVolume()
{
    return false;
}

std::shared_ptr<BSDF> LightEmitting::createBSDF(const Computation& _comp)
{
    return std::make_shared<LightEmittingBSDF>(_comp);
}

bool LightEmitting::scatter(
            const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered
            ) const
{
    return false; // does not scatter light
}

bool LightEmitting::hasAlbedo() const
{
    return false; // does not have albedo
}

ngl::Vec4 LightEmitting::albedo() const
{
    return m_emitColor; // the color of the light emitted
}
