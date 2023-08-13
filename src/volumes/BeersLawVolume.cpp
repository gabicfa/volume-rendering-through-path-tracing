#include "volumes/BeersLawVolume.h"
#include "Intersection.h"
#include <algorithm>
#include <cmath>


BeersLawVolume::BeersLawVolume(const ngl::Vec3 &absorption, Computation &comp)
    : Volume(comp), m_absorption(absorption) {}

/// @brief The BeersLawVolume class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// Implementation of the integrate method for BeersLawVolume. Determines how light is integrated as it passes through 
// the volume governed by Beer's Law, which accounts for absorption.
bool BeersLawVolume::integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
        &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s,  RendererServices &rs, Scene &scene) 
{
    // Intersect the volume with a ray from the computation point in the given direction.
    auto intersections = s.intersect(Ray(m_comp.point, wi.direction()));
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    // If there's no intersection, return false.
    if (i == Intersection()) {
        return false;
    }

    // Set default radiance value.
    L = ngl::Vec3(0, 0, 0);

    // Calculate points P0 and P1 for transmittance calculations.
    auto P1 = m_comp.point;
    auto P0 = m_comp.point + wi.direction() * i.t();
    P = P0;

    // Compute transmittance based on the distance between P0 and P1.
    transmittance = this->transmittance(P0, P1);

    // Set default weight and output ray direction.
    weight = ngl::Vec3(1.0, 1.0, 1.0);
    wo = Ray(P, wi.direction());

    return true;
}

// Implementation of the transmittance method for BeersLawVolume.
// Calculates the light transmittance through the volume based on Beer's Law.
// It calculates the attenuation due to absorption using an exponential function over the distance between two points.
ngl::Vec3 BeersLawVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    float distance = (P0 - P1).length();
    return ngl::Vec3(std::exp(m_absorption[0] * -distance), 
                     std::exp(m_absorption[1] * -distance), 
                     std::exp(m_absorption[2] * -distance));
}
//end citation