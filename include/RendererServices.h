#ifndef RENDERERSERVICES_H
#define RENDERERSERVICES_H

#include <random>
#include "Ray.h"
#include "Computation.h"
#include "AreaLight.h"

#include <ngl/Vec3.h>
#include <ngl/Vec4.h>


class RendererServices {
public:
    RendererServices() = default;
    RendererServices(AreaLight _light);
    float MISWeight(int nsamps1, float pdf1, int nsamps2, float pdf2);
    void generateLightSample(const Computation &_comp, ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance);
    void evaluateLightSample(const Computation &_comp, const ngl::Vec4 &sampleDirection, ngl::Vec3 &L, float &pdf, ngl::Vec3 &beamTransmittance);
    void evaluateLightSample(const Computation &_comp, const ngl::Vec3 &sampleDirection, ngl::Vec3 &L, float &pdf);
    private:
        AreaLight m_light;
};

#endif