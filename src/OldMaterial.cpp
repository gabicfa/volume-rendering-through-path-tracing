#include "OldMaterial.h"
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include <cmath>

ngl::Vec3 OldMaterial::color() const
{
    return m_color;
}

void OldMaterial::color(ngl::Vec3 _c)
{
    m_color = _c;
}

float OldMaterial::ambient() const
{
    return m_ambient;
}

void OldMaterial::ambient(float _a)
{
    m_ambient = _a;
}

float OldMaterial::diffuse() const
{
    return m_diffuse;
}

void OldMaterial::diffuse(float _d)
{
    m_diffuse = _d;
}

float OldMaterial::specular() const
{
    return m_specular;
}

void OldMaterial::specular(float _s)
{
    m_specular = _s;
}

float OldMaterial::shininess() const
{
    return m_shininess;
}

void OldMaterial::shininess(float _s)
{
    m_shininess = _s;
}

bool OldMaterial::operator==(const OldMaterial& other) const
{
    return m_color == other.color() && 
    m_ambient == other.ambient() &&
    m_diffuse == other.diffuse() &&
    m_specular == other.specular() &&
    m_shininess == other.shininess();
}

/// @brief light on material
/// Modified from :
/// Buck Jamis (2019). The Ray Tracer Challenge. Raleigh, North Carolina:The Pragmatic Bookshelf 
ngl::Vec3 OldMaterial::lighting(Light _l, ngl::Vec4 _pos, ngl::Vec4 _eye, ngl::Vec4 _normal)
{
    // combine the surface color with the light's color/intensity
    auto effectiveColor = m_color * _l.intensity();

    // find the direction to the light source
    auto l = _l.position() - _pos;
    auto light = l;
    if (l.length() > 0)
    {
        light = l.normalize();
    }

    // compute the ambient contribution
    ngl::Vec3 ambient = effectiveColor * m_ambient;
    auto lightDotNormal = light.dot(_normal);
    ngl::Vec3 diffuse;
    ngl::Vec3 specular;

    // lightDotNormal represents the cosine of the angle between the 
    // light vector and the normal vector. A negative number means the 
    // light is on the other side of the surface.
    if (lightDotNormal < 0.0f) 
    {
        diffuse = ngl::Vec3(0.0f, 0.0f, 0.0f);
        specular = ngl::Vec3(0.0f, 0.0f, 0.0f);
    }
    else
    {
        // compute the diffuse contribution
        diffuse = effectiveColor * m_diffuse * lightDotNormal;
        
        // reflectDotEye represents the cosine of the angle between the
        // reflection vector and the eye vector. A negative number means the 
        // light reflects away from the eye.
        auto reflect = (-light).toVec3().reflect(_normal.toVec3());
        auto reflectDotEye = ngl::Vec4(reflect).dot(_eye);
        if (reflectDotEye <= 0.0f)
        {
            specular = ngl::Vec3(0.0f, 0.0f, 0.0f);
        }
        else
        {
            // compute the specular contribution
            auto factor = pow(reflectDotEye, m_shininess);
            specular = _l.intensity() * m_specular * factor;
        }
    }
    
    // Add the three contributions together to get the final shading
    return ambient + diffuse + specular;
}
/// end of Citation