#include "materials/BeersLawHeterogeneousMaterial.h"
#include "Computation.h"
#include "Ray.h"

BeersLawHeterogeneousMaterial::BeersLawHeterogeneousMaterial(float maxAbsorption, int absorptionProperty) : m_maxAbsorption(maxAbsorption), m_absorptionProperty(absorptionProperty) {}

BeersLawHeterogeneousMaterial::~BeersLawHeterogeneousMaterial() {}

std::shared_ptr<BSDF> BeersLawHeterogeneousMaterial::createBSDF(const Computation& _comp)
{
    return std::make_shared<TrivialBSDF>(_comp);
}

bool BeersLawHeterogeneousMaterial::hasVolume()
{
    return true;
}

std::shared_ptr<Volume> BeersLawHeterogeneousMaterial::createVolume(Computation& _comp)
{
    return std::make_shared<BeersLawHeterogeneousVolume>(m_maxAbsorption, m_absorptionProperty, _comp);
}