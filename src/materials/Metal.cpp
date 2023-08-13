#include "materials/Metal.h"
#include "Utility.h"
#include "Ray.h"
#include "Computation.h"

Metal::Metal(const ngl::Vec4& _a) : m_albedo(_a) {}

// The Metal material does not have a volumetric component.
bool Metal::hasVolume()
{
    return false;
}

// Creates a MetalBSDF instance for this metallic material.
std::shared_ptr<BSDF> Metal::createBSDF(const Computation& _comp)
{
    return std::make_shared<MetalBSDF>(_comp);
}

ngl::Vec4 Metal::albedo() const
{
    return m_albedo;
}
