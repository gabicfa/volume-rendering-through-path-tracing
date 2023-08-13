#include "materials/SingleScatterHomogeneousMaterial.h"
#include "Computation.h"
#include "Ray.h"

// Constructor initializes the material with given scattering albedo and extinction coefficients.
SingleScatterHomogeneousMaterial::SingleScatterHomogeneousMaterial(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction) 
    : m_scatteringAlbedo(scatteringAlbedo), m_extinction(extinction) {}

SingleScatterHomogeneousMaterial::~SingleScatterHomogeneousMaterial() {}


/// @brief The SingleScatterHomogeneousMaterial class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// Creates an IsotropicPhaseBSDF for light interactions, which assumes light scatter equally in all directions.
std::shared_ptr<BSDF> SingleScatterHomogeneousMaterial::createBSDF(const Computation& _comp)
{
    return std::make_shared<IsotropicPhaseBSDF>(_comp);
}

// Indicates that this material does have volume properties, which determine how light interacts within the material volume.
bool SingleScatterHomogeneousMaterial::hasVolume()
{
    return true;
}

// Creates a SingleScatterHomogeneousVolume, which models the behavior of single scattering in a homogeneous medium.
std::shared_ptr<Volume> SingleScatterHomogeneousMaterial::createVolume(Computation& _comp)
{
    return std::make_shared<SingleScatterHomogeneousVolume>(m_scatteringAlbedo, m_extinction, _comp);
}

// end of citation