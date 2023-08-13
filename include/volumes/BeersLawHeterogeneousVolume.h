#ifndef BEERSLAWHETEROGENEOUSVOLUME_H_
#define BEERSLAWHETEROGENEOUSVOLUME_H_

#include "Volume.h"
#include "ngl/Vec3.h"
#include "Perlin.h"

class BeersLawHeterogeneousVolume : public Volume 
{
    public:
        BeersLawHeterogeneousVolume(float maxAbsorption, Computation &comp);
        virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
                &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs, Scene &scene) override;
        virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;

    protected:
        const float m_maxAbsorption;
        Perlin m_perlin;
};

#endif
