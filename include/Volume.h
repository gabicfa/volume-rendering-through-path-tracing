#ifndef VOLUME_H_
#define VOLUME_H_
#include <iostream>

#include<ngl/Vec3.h>
#include<ngl/Vec4.h>
#include "Computation.h"
#include "Ray.h"
#include "Shape.h"
#include "Scene.h"
#include "RendererServices.h"

/// @brief The Volume class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.

// The Volume class provides an abstract interface for volume integration in a rendering system. 
// It models the behavior of light as it passes through a participating medium, such as fog or smoke.
class Volume
{
    public:
        // Constructor initializes the volume with the computation context.
        Volume(Computation &comp) : m_comp(comp) {}

        // Virtual destructor.
        virtual ~Volume() {}

        // The Integrate method initiates the volume integration.
        // It takes as input a ray ω with origin x0, indicating the volume interval direction, 
        // and a RendererServices object for use during integration.
        virtual bool integrate(
            const Ray &wi,                // The input ray with direction ω originating from x0, denoting the direction of the volume interval.
            ngl::Vec3 &L,                 // Output radiance along the ray ω. This is the estimated contribution of light traveling along the ray through the volume.
            ngl::Vec3 &transmittance,     // Output beam transmittance over the volume integration interval. Represents how much light gets through the volume without being absorbed or scattered.
            ngl::Vec3 &weight,            // Output weight of the radiance estimate L. This is used to modulate the contribution of the ray to the final image, considering factors like scattering and absorption in the volume.
            ngl::Vec4 &P,                 // Output hit point at the end of the volume integration interval. The volume integrator determines the distance and returns this point.
            Ray &wo,                      // Output incident ray direction into the hit point P. It indicates where the light is coming from at the end of the volume interval.
            Shape &s,                     // Output geometry corresponding to the end of the volume integration interval. This provides details about the shape or surface where the ray exits the volume.
            RendererServices &rs,         // A RendererServices object provided as a tool for the volume during integration. This object can offer services like sampling.
            Scene &scene                  // The scene in which the volume integration is taking place. This can be used to access other objects or details in the scene.
        ) = 0;


        // Returns the beam transmittance between two points P0 and P1 in the volume.
        virtual ngl::Vec3 transmittance(const ngl::Vec4 &P0, const ngl::Vec4 &P1) = 0;

    protected:
        // Reference to the computation context.
        Computation &m_comp;
};
// end citation

#endif
