#ifndef BSDF_H_
#define BSDF_H_

#include "Computation.h"

// The BSDF (Bidirectional Scattering Distribution Function) class is an abstract base class
// used to define how light interacts with surfaces, depending on the angle of incidence and the wavelength of light.
// Different materials can define different BSDFs to simulate their unique appearance.

/// @brief The BSDF abstract base class
/// Modified from :
/// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.
class BSDF {
    public:
        // Constructor initializes the BSDF with a Computation reference.
        // The Computation holds data about a ray interacting a surface.
        BSDF(const Computation &comp) : m_comp(comp) {}

        // Virtual destructor to ensure proper cleanup in derived classes.
        virtual ~BSDF() {}

        // The evaluateSample method evaluates the response of the BSDF to a light sample.
        // Given an incoming light ray with direction sampleDirection and the outgoing ray 
        // direction specified in Computation.eye, it calculates the resulting light 
        // intensity (L) and the probability density function (pdf) of that sample direction.
        virtual void evaluateSample(const Computation& _comp, const ngl::Vec4& sampleDirection, ngl::Vec3& L, float &pdf) = 0;

        // The generateSample method is used to sample the BSDF for a particular interaction.
        // It generates an outgoing ray direction (sampleDirection) based on evaluating a BRDF.
        // Additionally, it calculates the light intensity (L) and the associated probability 
        // density function (pdf) of that generated ray direction.
        virtual void generateSample(const Computation& _comp, ngl::Vec4& sampleDirection, ngl::Vec3& L, float& pdf) = 0;

    protected:
        // Reference to the Computation, which contains details about the point of intersection, 
        // the normal at that point, and other related data.
        const Computation &m_comp;
};
// end of citation

#endif
