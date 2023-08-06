#include "volumes/SingleScatterHeterogeneousVolume.h"
#include "Computation.h"
#include "Utility.h"
#include "bsdfs/IsotropicPhaseBSDF.h"
#include <ngl/Vec4.h>
#include <memory>
#include "Intersection.h"


SingleScatterHeterogeneousVolume::SingleScatterHeterogeneousVolume(const ngl::Vec3 &scatteringAlbedoProperty, 
                                                                   const ngl::Vec3 &maxExtinction, 
                                                                   int extinctionProperty, Computation &comp)
    : Volume(comp), m_scatteringAlbedo(scatteringAlbedoProperty), m_maxExtinction(channelAvg(maxExtinction)),
      m_extinctionProperty(extinctionProperty) {}

ngl::Vec3 SingleScatterHeterogeneousVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    float distance = (P0 - P1).length();
    auto dir = (P1 - P0) / distance;
    bool terminated = false;
    float t = 0;

    do {
        float zeta = randomDouble(0.0,1.0);
        t = t - log(1 - zeta) / m_maxExtinction;
        if (t > distance) {
            break; // Did not terminate in the volume
        }
        // Update the shading context
        ngl::Vec4 P = P0 + t * dir;
        // Recompute the local absorption after updating the shading context
        float extinction = m_perlin.noise(P);
        float xi = randomDouble(0.0,1.0);
        if (xi < (extinction / m_maxExtinction))
            terminated = true;
    } while (!terminated);
    
    if (terminated)
        return ngl::Vec3(0.0, 0.0, 0.0);
    else
        return ngl::Vec3(1.0, 1.0, 1.0);
}

bool SingleScatterHeterogeneousVolume::integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
            &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s,  RendererServices &rs)
{
    ngl::Vec4 P0 = m_comp.point;
    auto intersections = s.intersect(Ray(m_comp.point, wi.direction()));
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    if (i == Intersection()) {
        return false;
    }

    float distance = (P - P0).length();
    bool terminated = false;
    float t = 0;

    do {
        float zeta = randomDouble();
        t = t - log(1 - zeta) / m_maxExtinction;
        if (t > distance) {
            break;  // Did not terminate in the volume
        }

        // Update the shading context
        ngl::Vec4 Pl = P0 + t * wi.direction();
        m_comp.point = Pl;
        // Here, you would call your recompute function

        // Recompute the local extinction after updating the shading context
        float extinction = m_perlin.noise(Pl);
        float xi = randomDouble();
        if (xi < extinction / m_maxExtinction)
            terminated = true;
    } while (!terminated);

    if (terminated) {
        // Compute direct lighting after evaluating the local scattering albedo and extinction
        auto p1 = m_perlin.noise(m_comp.point);
        ngl::Vec3 scatteringAlbedo = ngl::Vec3(p1, p1, p1);
        ngl::Vec3 extinction = ngl::Vec3(p1+ randomDouble(), p1+ randomDouble(), p1+ randomDouble());
        IsotropicPhaseBSDF phaseBSDF(m_comp);
        L = ngl::Vec3(0.0f, 0.0f, 0.0f);
        ngl::Vec3 lightL, bsdfL, beamTransmittance;
        float lightPdf, bsdfPdf;
        ngl::Vec4 sampleDirection;
        rs.generateLightSample(m_comp, sampleDirection, lightL, lightPdf, beamTransmittance);
        phaseBSDF.evaluateSample(m_comp, sampleDirection, bsdfL, bsdfPdf);
        L += lightL * bsdfL * beamTransmittance * scatteringAlbedo * extinction *
                rs.MISWeight(1, lightPdf, 1, bsdfPdf) / lightPdf;
        phaseBSDF.generateSample(m_comp, sampleDirection, bsdfL, bsdfPdf);
        rs.evaluateLightSample(m_comp, sampleDirection, lightL, lightPdf, beamTransmittance);
        L += lightL * bsdfL * beamTransmittance * scatteringAlbedo * extinction *
                rs.MISWeight(1, lightPdf, 1, bsdfPdf) / bsdfPdf;
        transmittance = ngl::Vec3(0.0f,0.0f,0.0f);
        ngl::Vec3 pdf = extinction; 
        weight = ngl::Vec3(1.0, 1.0, 1.0) / pdf;
    } else {
        transmittance = ngl::Vec3(1.0f,1.0f,1.0f);
        weight = ngl::Vec3(1.0f,1.0f,1.0f);
    }
    wo = Ray(P, wi.direction());
    return true;
}

