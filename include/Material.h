#ifndef MATERIAL_H_
#define MATERIAL_H_

#include <iostream>
#include "Ray.h"
#include "BSDF.h"

class Volume;
class Computation;

// The Material class represents a general material interface in a rendering system.
// It can produce a BSDF to model surface interactions and can also have a volumetric component.
class Material
{
    public:

        /// @brief Modifications to Material class to add volumetric component to it
        /// Modified from :
        /// Fong et al (2017). Production Volume Rendering. In: SIGGRAPH 2017 Course. Los Angeles, California.
        // Creates and returns a BSDF object to model the surface properties of this material.
        // The specific BSDF produced is determined by the derived material classes.
        virtual std::shared_ptr<BSDF> createBSDF(const Computation& _comp) = 0;

        // Determines if the material has a volumetric component.
        virtual bool hasVolume() = 0;

        // Creates and returns a Volume object to model the volumetric properties of this material.
        // By default, materials don't have a volume and this method returns nullptr.
        // Derived classes with volumetric properties should override this method.
        virtual std::shared_ptr<Volume> createVolume(Computation &_comp)
        {
            return nullptr;
        }
        // end of citation

        // Returns the albedo of the material. This is a measure of its reflectance.
        // By default, it returns a white color. Derived classes can override to provide different albedo values.
        virtual ngl::Vec4 albedo() const { return ngl::Vec4(1.0f, 1.0f, 1.0f, 1.0f); }
};

#endif
