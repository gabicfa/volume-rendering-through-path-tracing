#ifndef BEERSLAWVOLUME_H_
#define BEERSLAWVOLUME_H_

#include "Volume.h"
#include "ngl/Vec3.h"

class BeersLawVolume : public Volume {
public:
    BeersLawVolume(const ngl::Vec3 &absorption, Computation &comp);
    virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
            &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs) override;
    virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;

protected:
    const ngl::Vec3 m_absorption;
};

#endif
