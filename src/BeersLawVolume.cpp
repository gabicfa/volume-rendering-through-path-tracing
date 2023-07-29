#include "BeersLawVolume.h"
#include "Intersection.h"
#include <algorithm>
#include <cmath>


BeersLawVolume::BeersLawVolume(const ngl::Vec3 &absorption, Computation &comp)
    : Volume(comp), m_absorption(absorption) {}

bool BeersLawVolume::integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
        &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s) {
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

ngl::Vec3 BeersLawVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    float distance = (P0 - P1).length();
    return ngl::Vec3(std::exp(m_absorption[0] * -distance), 
                     std::exp(m_absorption[1] * -distance), 
                     std::exp(m_absorption[2] * -distance));
}
