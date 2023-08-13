#include "volumes/EmptyVolume.h"

EmptyVolume::EmptyVolume(Computation &comp) 
    : Volume(comp) {}

EmptyVolume::~EmptyVolume() {}

/// @brief The EmptyVolume class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// Implementation of the integrate method for EmptyVolume.
bool EmptyVolume::integrate(
    const Ray &wi, ngl::Vec3 &L, ngl::Vec3 &transmittance, ngl::Vec3 &weight, 
    ngl::Vec4 &P, Ray &wo, Shape &s,  RendererServices &rs, Scene &scene
) {
    // Create a ray from the current computation point in the given direction.
    Ray r(m_comp.point, wi.direction());
    auto intersections = s.intersect(r);
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);
    Intersection empty = Intersection();

    // If there's no intersection, return false.
    if (i == empty) {
        return false;
    }

    // Set the hit point.
    P = r.position(i.t());

    // Set default values for radiance, transmittance, and weight.
    L = ngl::Vec3(0.0, 0.0, 0.0);
    transmittance = ngl::Vec3(1.0, 1.0, 1.0);
    weight = ngl::Vec3(1.0, 1.0, 1.0);
    wo = Ray(P, wi.direction());

    return true;
}

// Implementation of the transmittance method for EmptyVolume.
// Always returns full transparency for an empty volume.
ngl::Vec3 EmptyVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    return ngl::Vec3(1.0, 1.0, 1.0);
}

//end citation