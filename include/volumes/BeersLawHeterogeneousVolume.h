#ifndef BEERSLAWHETEROGENEOUSVOLUME_H_
#define BEERSLAWHETEROGENEOUSVOLUME_H_

#include "Volume.h"
#include "ngl/Vec3.h"
#include "Perlin.h"

// The BeersLawHeterogeneousVolume class extends the generic Volume class to implement 
// Beer's Law in a heterogeneous medium, meaning the absorption properties can vary 
// throughout the medium. This is in contrast to a homogeneous medium where the absorption 
// is uniform everywhere.
class BeersLawHeterogeneousVolume : public Volume 
{
    public:
        BeersLawHeterogeneousVolume(float maxAbsorption, Computation &comp);

        virtual bool integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
                &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs, Scene &scene) override;
        virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;

    protected:
        // Member variable representing the maximum absorption value of the medium.
        const float m_maxAbsorption;

        // A Perlin noise generator which is used to simulate the heterogeneous nature of the volume.
        Perlin m_perlin;
};

#endif
