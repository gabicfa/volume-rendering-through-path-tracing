#ifndef SINGLESCATTERHOMOGENEOUSVOLUME_H_
#define SINGLESCATTERHOMOGENEOUSVOLUME_H_

#include "Volume.h"
#include "ngl/Vec3.h"

// Represents a homogeneous volume in which light undergoes single scattering events.
// This volume uses the principle of single scattering in which light photons scatter
// only once before reaching the observer.
class SingleScatterHomogeneousVolume : public Volume {
public:
    SingleScatterHomogeneousVolume(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction, Computation &comp);
    virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3 &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs, Scene &scene) override;
    virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;

protected:
    const ngl::Vec3 m_scatteringAlbedo;  // Proportion of the scattered light that is scattered by the particles in the medium.
    const ngl::Vec3 m_extinction;        // Describes how the light intensity decays as it travels through the medium.
};

#endif
