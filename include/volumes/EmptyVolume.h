#ifndef EMPTYVOLUME_H_
#define EMPTYVOLUME_H_

#include "Volume.h"
#include "Intersection.h"
#include<ngl/Vec3.h>
#include<ngl/Vec4.h>

// The EmptyVolume class represents a volume that does not affect light paths through it.
// Typically, such a volume does not absorb, scatter or emit light.
class EmptyVolume : public Volume {
public:
    EmptyVolume(Computation &comp);
    virtual ~EmptyVolume() override;

    virtual bool integrate(
        const Ray &wi, ngl::Vec3 &L, ngl::Vec3 &transmittance, ngl::Vec3 &weight, 
        ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs, Scene &scene
    ) override;
    
    virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;
};

#endif