#include "volumes/SingleScatterHomogeneousVolume.h"
#include "Intersection.h"
#include "Utility.h"
#include "bsdfs/IsotropicPhaseBSDF.h"
#include <algorithm>
#include <cmath>

SingleScatterHomogeneousVolume::SingleScatterHomogeneousVolume(ngl::Vec3 scatteringAlbedo, ngl::Vec3 extinction, Computation &comp)
    : Volume(comp), m_scatteringAlbedo(scatteringAlbedo), m_extinction(extinction) {}
/// @brief The SingleScatterHomogeneousVolume class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.
// Calculates the interaction of a ray with the homogeneous volume, including its scattering and extinction effects.
bool SingleScatterHomogeneousVolume::integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3 &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s, RendererServices &rs, Scene &scene) {
    
    // Find the intersections of the ray with the volume's boundary.
    auto intersections = s.intersect(Ray(m_comp.point, wi.direction()));
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    if (i == Intersection()) {
        return false;
    }

    // Compute the transmittance over the entire distance between ray's origin and hit point.
    ngl::Vec4 hitPoint = m_comp.point + wi.direction() * i.t();
    transmittance = this->transmittance(m_comp.point, hitPoint);
    
    // Calculate the distance at which a scattering event occurs.
    float xi = randomDouble();
    float scatterDistance = -logf(1.0f - xi * (1.0f - channelAvg(transmittance))) / channelAvg(m_extinction);

    // Update the computation to the scattering location.
    ngl::Vec4 Pscatter = m_comp.point + scatterDistance * wi.direction();
    m_comp.point = Pscatter;
    m_comp.recompute();
    
    // Compute the contribution from light sources considering the phase function.
     IsotropicPhaseBSDF phaseBSDF(m_comp);
    L = ngl::Vec3(0.0f, 0.0f, 0.0f);
    ngl::Vec3 lightL, bsdfL, beamTransmittance;
    float lightPdf, bsdfPdf;
    ngl::Vec4 sampleDirection;
    rs.generateLightSample(m_comp, sampleDirection, lightL, lightPdf, beamTransmittance, scene);
    phaseBSDF.evaluateSample(m_comp, sampleDirection, bsdfL, bsdfPdf);
    L += lightL * bsdfL * beamTransmittance * rs.MISWeight(1, lightPdf, 1, bsdfPdf) / lightPdf;


    phaseBSDF.generateSample(m_comp, sampleDirection, bsdfL, bsdfPdf);
    rs.evaluateLightSample(m_comp, sampleDirection, lightL, lightPdf, beamTransmittance, scene);
    L += lightL * bsdfL * beamTransmittance * rs.MISWeight(1, lightPdf, 1, bsdfPdf) / bsdfPdf;

    ngl::Vec3 trasmission(exp(m_extinction.m_x * -scatterDistance), exp(m_extinction.m_y *
        -scatterDistance), exp(m_extinction.m_z * -scatterDistance));
    L = L * (m_extinction * m_scatteringAlbedo * trasmission);

    // This weight is 1 over the PDF normalized to the total transmission
    weight = (ngl::Vec3(1.0, 1.0, 1.0) - transmittance) / (trasmission * m_extinction);
    wo = Ray(P, wi.direction());
    
    return true;
}

// Computes the transmittance of light between two points in the volume, accounting for extinction.
ngl::Vec3 SingleScatterHomogeneousVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    float distance = (P0 - P1).length();
    auto transmittance = ngl::Vec3(exp(m_extinction.m_x * -distance), exp(m_extinction.m_y * -distance),
                     exp(m_extinction.m_z * -distance));
    return transmittance;
}
//end citation