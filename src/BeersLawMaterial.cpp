#include "BeersLawMaterial.h"
#include "Computation.h"
#include "Ray.h"

BeersLawMaterial::BeersLawMaterial(const ngl::Vec3& extinction, ngl::Vec4 _a) : m_extinction(extinction), m_albedo(_a) {}

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

bool BeersLawMaterial::scatter(const Ray& _rIn, const Computation& _comp, ngl::Vec3& attenuation, Ray& scattered) const
{
    return false;
}

ngl::Vec4 BeersLawMaterial::albedo() const
{
    return m_albedo;
}
