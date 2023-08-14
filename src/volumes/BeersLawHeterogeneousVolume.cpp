#include "volumes/BeersLawHeterogeneousVolume.h"
#include "Intersection.h"
#include "Utility.h"
#include <algorithm>
#include <cmath>

// Constructor initializes the volume with the given maximum absorption coefficient and computation reference.
BeersLawHeterogeneousVolume::BeersLawHeterogeneousVolume(float maxAbsorption, Computation &comp)
    : Volume(comp), m_maxAbsorption(maxAbsorption) {}

/// @brief The BeersLawHeterogeneousVolume class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.
// Implementation of the integrate function. Determines if a ray intersects with the volume, 
// and computes the transmittance using Beer's Law for a heterogeneous medium.
bool BeersLawHeterogeneousVolume::integrate(const Ray &wi, ngl::Vec3 &L, ngl::Vec3
        &transmittance, ngl::Vec3 &weight, ngl::Vec4 &P, Ray &wo, Shape &s,  RendererServices &rs, Scene &scene) {
    
    // Find intersections of the incoming ray with the shape.
    auto intersections = s.intersect(Ray(m_comp.point, wi.direction()));
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    // If the intersection is empty, return false.
    if (i == Intersection()) {
        return false;
    }

    // Initialize light intensity to a zero vector.
    L = ngl::Vec3(0, 0, 0);

    // Define starting and ending points for the ray segment within the volume.
    auto P1 = m_comp.point;
    auto P0 = m_comp.point + wi.direction() * i.t();
    P = P0;

    // Compute transmittance between P0 and P1 in the heterogeneous medium.
    transmittance = this->transmittance(P0, P1);

    // Set the weight (which can be used in multiple scattering scenarios or for importance sampling).
    weight = ngl::Vec3(1.0, 1.0, 1.0);

    // Set the outgoing ray with the computed position and original direction.
    wo = Ray(P, wi.direction());

    return true;
}

// Calculates the transmittance of light between two points in the heterogeneous medium 
// using Monte Carlo delta tracking. The absorption varies based on the Perlin noise.
ngl::Vec3 BeersLawHeterogeneousVolume::transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) {
    
    // Calculate the distance between the two points.
    float distance = (P0 - P1).length();
    auto dir = (P1 - P0) / distance;
    bool terminated = false;  // A flag to determine if the ray terminated within the medium.
    float t = 0;

    // Monte Carlo delta tracking loop to sample absorption along the ray's path in the heterogeneous medium.
    do {
        // Sample a random point along the ray.
        float zeta = randomFloat(0.0,1.0);
        t = t - log(1 - zeta) / m_maxAbsorption;
        
        // If the sampled point is outside the medium, break the loop.
        if (t > distance) {
            break;
        }

        // Calculate the absorption at the sampled point using Perlin noise.
        ngl::Vec4 P = P0 + t * dir;
        float absorption = m_perlin.noise(P);

        // Sample another random number to determine if the ray terminates at the sampled point.
        float xi = randomFloat(0.0,1.0);
        if (xi < (absorption / m_maxAbsorption))
            terminated = true;

    } while (!terminated);
    
    // If the ray terminated within the volume, transmittance is zero. Otherwise, it's one.
    if (terminated)
        return ngl::Vec3(0.0, 0.0, 0.0);
    else
        return ngl::Vec3(1.0, 1.0, 1.0);
}
//end citation