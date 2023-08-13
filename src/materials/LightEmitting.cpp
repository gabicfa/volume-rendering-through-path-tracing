#include "materials/LightEmitting.h"

LightEmitting::LightEmitting(const ngl::Vec4& _a) : m_emitColor(_a) {}

// Light-emitting materials are considered to be non-volumetric in this context.
bool LightEmitting::hasVolume()
{
    return false;
}

// Creates a LightEmittingBSDF for light interactions with this light-emitting material.
std::shared_ptr<BSDF> LightEmitting::createBSDF(const Computation& _comp)
{
    return std::make_shared<LightEmittingBSDF>(_comp);
}

// Retrieves the emission color of the material.
ngl::Vec4 LightEmitting::albedo() const
{
    return m_emitColor;
}
