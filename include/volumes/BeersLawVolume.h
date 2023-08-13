#ifndef BEERSLAWVOLUME_H_
#define BEERSLAWVOLUME_H_

#include "Volume.h"
#include "ngl/Vec3.h"

// The BeersLawVolume class extends the generic Volume class and provides an implementation
// based on Beer's Law, which deals with the attenuation (or absorption) of light as it travels 
// through a medium.
class BeersLawVolume : public Volume 
{
    public:
        BeersLawVolume(const ngl::Vec3 &absorption, Computation &comp);
        virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
                &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs, Scene &scene) override;
        virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;

    protected:
        // Member variable representing the absorption coefficient of the medium. Determines how much 
        // light is absorbed as it travels through the medium.
        const ngl::Vec3 m_absorption;
};

#endif
