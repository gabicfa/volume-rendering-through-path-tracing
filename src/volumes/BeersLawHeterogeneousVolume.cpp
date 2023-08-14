#include "volumes/BeersLawHeterogeneousVolume.h"
#include "Intersection.h"
#include "Utility.h"
#include <algorithm>
#include <cmath>

BeersLawHeterogeneousVolume::BeersLawHeterogeneousVolume(float maxAbsorption, int absorptionProperty, Computation &comp)
    : Volume(comp), m_maxAbsorption(maxAbsorption), m_absorptionProperty(absorptionProperty) {}

bool BeersLawHeterogeneousVolume::integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
        &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s,  RendererServices &rs, Scene &scene) {
    auto intersections = s.intersect(Ray(m_comp.point, wi.direction()));
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    if (i == Intersection()) {
        return false;
    }

    L = ngl::Vec3(0, 0, 0);
    auto P1 = m_comp.point;
    auto P0 = m_comp.point + wi.direction() * i.t();
    P = P0;
    transmittance = this->transmittance(P0, P1);
    weight = ngl::Vec3(1.0, 1.0, 1.0);
    wo = Ray(P, wi.direction());

    return true;
}

ngl::Vec3 BeersLawHeterogeneousVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    float distance = (P0 - P1).length();
    auto dir = (P1 - P0) / distance;
    bool terminated = false;
    float t = 0;

    do {
        float zeta = randomFloat(0.0,1.0);
        t = t - log(1 - zeta) / m_maxAbsorption;
        if (t > distance) {
            break; // Did not terminate in the volume
        }
        // Update the shading context
        ngl::Vec4 P = P0 + t * dir;
        // Recompute the local absorption after updating the shading context
        float absorption = m_perlin.noise(P);
        float xi = randomFloat(0.0,1.0);
        if (xi < (absorption / m_maxAbsorption))
            terminated = true;
    } while (!terminated);
    
    if (terminated)
        return ngl::Vec3(0.0, 0.0, 0.0);
    else
        return ngl::Vec3(1.0, 1.0, 1.0);
}
