#include "SingleScatterHomogeneousMaterial.h"
#include "Computation.h"
#include "Ray.h"

SingleScatterHomogeneousMaterial::SingleScatterHomogeneousMaterial(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction) 
    : m_scatteringAlbedo(scatteringAlbedo), m_extinction(extinction) {}

SingleScatterHomogeneousMaterial::~SingleScatterHomogeneousMaterial() {}

std::shared_ptr<BSDF> SingleScatterHomogeneousMaterial::createBSDF(const Computation& _comp)
{
    return std::make_shared<IsotropicPhaseBSDF>(_comp);
}

bool SingleScatterHomogeneousMaterial::hasVolume()
{
    return true;
}

std::shared_ptr<Volume> SingleScatterHomogeneousMaterial::createVolume(Computation& _comp)
{
    return std::make_shared<SingleScatterHomogeneousVolume>(m_scatteringAlbedo, m_extinction, _comp);
}

bool SingleScatterHomogeneousMaterial::scatter(const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered) const
{
    return false;
}
