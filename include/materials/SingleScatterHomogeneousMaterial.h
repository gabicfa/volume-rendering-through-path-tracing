#ifndef SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_
#define SINGLE_SCATTER_HOMOGENEOUS_MATERIAL_H_

#include "Material.h"
#include "bsdfs/IsotropicPhaseBSDF.h"
#include "volumes/SingleScatterHomogeneousVolume.h"
#include "ngl/Vec3.h"

// The SingleScatterHomogeneousMaterial class represents a material in a homogeneous medium 
// that exhibits single scattering. Homogeneous means the properties of the medium are consistent 
// throughout. This material uses isotropic phase functions for light interactions and takes into 
// account scattering albedo and extinction.
class SingleScatterHomogeneousMaterial : public Material
{
public:
    SingleScatterHomogeneousMaterial(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction);
    virtual ~SingleScatterHomogeneousMaterial();

    std::shared_ptr<BSDF> createBSDF(const Computation& _comp) override;
    bool hasVolume() override;
    std::shared_ptr<Volume> createVolume(Computation& _comp) override;

private:
    const ngl::Vec3 m_scatteringAlbedo;    // The ratio of scattering to absorption for the material.
    const ngl::Vec3 m_extinction;          // Measures the attenuation of light as it passes through the material.
};

#endif
