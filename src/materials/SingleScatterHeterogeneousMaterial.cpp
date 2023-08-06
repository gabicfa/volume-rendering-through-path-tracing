#include "materials/SingleScatterHeterogeneousMaterial.h"
#include "Computation.h"
#include "Ray.h"

SingleScatterHeterogeneousMaterial::SingleScatterHeterogeneousMaterial(ngl::Vec3 scatteringAlbedo, ngl::Vec3 maxExtinction, int extinction) 
    : m_scatteringAlbedo(scatteringAlbedo), m_maxExtinction(maxExtinction), m_extinctionProperty(extinction) {}

SingleScatterHeterogeneousMaterial::~SingleScatterHeterogeneousMaterial() {}

std::shared_ptr<BSDF> SingleScatterHeterogeneousMaterial::createBSDF(const Computation& _comp)
{
    return std::make_shared<IsotropicPhaseBSDF>(_comp);
}

bool SingleScatterHeterogeneousMaterial::hasVolume()
{
    return true;
}

std::shared_ptr<Volume> SingleScatterHeterogeneousMaterial::createVolume(Computation& _comp)
{
    return std::make_shared<SingleScatterHeterogeneousVolume>(m_scatteringAlbedo, m_maxExtinction, m_extinctionProperty, _comp);
}