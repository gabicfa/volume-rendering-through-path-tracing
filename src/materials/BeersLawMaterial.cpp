#include "materials/BeersLawMaterial.h"
#include "Computation.h"
#include "Ray.h"

BeersLawMaterial::BeersLawMaterial(const ngl::Vec3& extinction) : m_extinction(extinction) {}

BeersLawMaterial::~BeersLawMaterial() {}

std::shared_ptr<BSDF> BeersLawMaterial::createBSDF(const Computation& _comp)
{
    return std::make_shared<TrivialBSDF>(_comp);
}

bool BeersLawMaterial::hasVolume()
{
    return true;
}

std::shared_ptr<Volume> BeersLawMaterial::createVolume(Computation& _comp)
{
    return std::make_shared<BeersLawVolume>(m_extinction, _comp);
}