#include "materials/BeersLawHeterogeneousMaterial.h"
#include "Computation.h"
#include "Ray.h"

// Constructor initializes the material with a given maximum absorption coefficient and an absorption property.
BeersLawHeterogeneousMaterial::BeersLawHeterogeneousMaterial(float maxAbsorption) : m_maxAbsorption(maxAbsorption) {}

BeersLawHeterogeneousMaterial::~BeersLawHeterogeneousMaterial() {}


/// @brief The BeersLawHeterogeneousMaterial class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// Creates a TrivialBSDF for light interactions with this Beer's Law material in a heterogeneous medium.
std::shared_ptr<BSDF> BeersLawHeterogeneousMaterial::createBSDF(const Computation& _comp)
{
    return std::make_shared<TrivialBSDF>(_comp);
}

// Indicates that this material does have volume properties, which determine how light interacts within the material volume.
bool BeersLawHeterogeneousMaterial::hasVolume()
{
    return true;
}

// Creates a BeersLawHeterogeneousVolume, which models the attenuation of light based on spatially varying properties of the medium.
std::shared_ptr<Volume> BeersLawHeterogeneousMaterial::createVolume(Computation& _comp)
{
    return std::make_shared<BeersLawHeterogeneousVolume>(m_maxAbsorption, _comp);
}
// end of citation