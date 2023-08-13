#include "materials/BeersLawMaterial.h"
#include "Computation.h"
#include "Ray.h"

BeersLawMaterial::BeersLawMaterial(const ngl::Vec3& extinction) : m_extinction(extinction) {}

BeersLawMaterial::~BeersLawMaterial() {}

/// @brief The BeersLawMaterial class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// Creates a TrivialBSDF for light interactions with this Beer's Law material.
// This BSDF represents a simple form of light reflection without any specific characteristics.
std::shared_ptr<BSDF> BeersLawMaterial::createBSDF(const Computation& _comp)
{
    return std::make_shared<TrivialBSDF>(_comp);
}

// Indicates that this material does have volume properties, which determine how light interacts within the material volume.
bool BeersLawMaterial::hasVolume()
{
    return true;
}

// Creates a BeersLawVolume, which models the attenuation of light as it passes through the volume of this material.
std::shared_ptr<Volume> BeersLawMaterial::createVolume(Computation& _comp)
{
    return std::make_shared<BeersLawVolume>(m_extinction, _comp);
}
//end of citation