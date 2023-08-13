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

ngl::Vec4 LightEmitting::albedo() const
{
    return m_emitColor;
}