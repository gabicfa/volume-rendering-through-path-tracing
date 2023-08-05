#include "volumes/EmptyVolume.h"

EmptyVolume::EmptyVolume(Computation &comp) 
    : Volume(comp) {}

EmptyVolume::~EmptyVolume() {}

bool EmptyVolume::integrate(
    const Ray &wi, ngl::Vec3 &L, ngl::Vec3 &transmittance, ngl::Vec3 &weight, 
    ngl::Vec4 &P, Ray &wo, Shape &s,  RendererServices &rs
) {
    Ray r(m_comp.point, wi.direction());
    auto intersections = s.intersect(r);
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);
    Intersection empty = Intersection();

    if (i == empty) {
        return false;
    }

    P = r.position(i.t());

    // If the ray successfully hit the object, 
    // we can define the outgoing ray (wo), transmittance, weight, and L.
    L = ngl::Vec3(0.0, 0.0, 0.0);
    transmittance = ngl::Vec3(1.0, 1.0, 1.0);
    weight = ngl::Vec3(1.0, 1.0, 1.0);
    wo = Ray(P, wi.direction());

    return true;
}

ngl::Vec3 EmptyVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    return ngl::Vec3(1.0, 1.0, 1.0);
}
