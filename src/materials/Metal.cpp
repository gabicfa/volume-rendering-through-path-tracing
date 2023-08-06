#include "materials/Metal.h"
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

ngl::Vec4 Metal::albedo() const
{
    return m_albedo;
}
