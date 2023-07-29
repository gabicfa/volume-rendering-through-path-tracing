#ifndef EMPTYVOLUME_H_
#define EMPTYVOLUME_H_

#include "Volume.h"
#include "Intersection.h"
#include<ngl/Vec3.h>
#include<ngl/Vec4.h>

class EmptyVolume : public Volume {
public:
    EmptyVolume(Computation &comp);
    virtual ~EmptyVolume() override;

    virtual bool integrate(
        const Ray &wi, ngl::Vec3 &L, ngl::Vec3 &transmittance, ngl::Vec3 &weight, 
        ngl::Vec4 &P, Ray &wo, Shape &s, Scene &scene
    ) override;
    
    virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) override;
};

#endif

