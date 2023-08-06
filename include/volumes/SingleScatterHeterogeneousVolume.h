#ifndef SINGLESCATTERHETEROGENEOUSVOLUME_H_
#define SINGLESCATTERHETEROGENEOUSVOLUME_H_

#include "Volume.h"
#include "Perlin.h"
#include "RendererServices.h"
#include "bsdfs/IsotropicPhaseBSDF.h"
#include <memory>
#include <ngl/Vec3.h>

class SingleScatterHeterogeneousVolume : public Volume
{
public:
    SingleScatterHeterogeneousVolume(const ngl::Vec3 &scatteringAlbedoProperty, const ngl::Vec3 &maxExtinction, 
                                     int extinctionProperty, Computation &comp);

    virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;
    virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
            &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s,  RendererServices &rs) override;

protected:
    ngl::Vec3 m_scatteringAlbedo;
    float m_maxExtinction;
    int m_extinctionProperty;
    Perlin m_perlin;
};

#endif