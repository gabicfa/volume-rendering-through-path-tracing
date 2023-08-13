#ifndef SINGLESCATTERHOMOGENEOUSVOLUME_H_
#define SINGLESCATTERHOMOGENEOUSVOLUME_H_

#include "Volume.h"
#include "ngl/Vec3.h"

class SingleScatterHomogeneousVolume : public Volume {
public:
    SingleScatterHomogeneousVolume(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction, Computation &comp);
    virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
            &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs, Scene &scene) override;
    virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;

protected:
    const ngl::Vec3 m_scatteringAlbedo;
    const ngl::Vec3 m_extinction;
};

#endif
