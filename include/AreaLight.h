#ifndef AREALIGHT_H
#define AREALIGHT_H

#include <ngl/Vec4.h>
#include <ngl/Vec3.h>

// AreaLight class represents an area light source in the scene.
// An area light emits light from a surface area, unlike point lights which emit from a single point.
class AreaLight {
public:
    AreaLight() = default;
    AreaLight(const ngl::Vec4& _center, const ngl::Vec4& _udir, const ngl::Vec4& _vdir, const ngl::Vec3& _intensity);

    // Accessors for the u-direction, v-direction, center, and intensity of the area light.
    ngl::Vec4 udir() const;
    ngl::Vec4 vdir() const;
    ngl::Vec4 center() const;
    ngl::Vec3 intensity() const;

    void sample(ngl::Vec4& _samplePoint, ngl::Vec3& _intensity) const;

private:
    ngl::Vec4 m_center; // Center position of the area light.
    ngl::Vec4 m_udir, m_vdir; // Direction vectors defining the area's orientation.
    ngl::Vec3 m_intensity; // Intensity of the light.
};

#endif