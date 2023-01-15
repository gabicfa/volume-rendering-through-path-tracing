#ifndef MATERIAL_H_
#define MATERIAL_H_
#include <iostream>
#include <ngl/Vec3.h>

#include "Light.h"

class Material
{
    public:
        Material()=default;
        ngl::Vec3 color() const;
        void color(ngl::Vec3 _c);
        float ambient() const;
        void ambient(float _a);
        float diffuse() const;
        void diffuse(float _d);
        float specular() const;
        void specular(float _s);
        float shininess() const;
        void shininess(float _s);
        bool operator==(const Material& other) const;
        ngl::Vec3 lighting(Light _l, ngl::Vec4 _pos, ngl::Vec4 _eye, ngl::Vec4 _normal);
    private:
        ngl::Vec3 m_color = ngl::Vec3(1.0f,1.0f,1.0f);
        float m_ambient = 0.1f;
        float m_diffuse = 0.9f;
        float m_specular = 0.9f;
        float m_shininess = 200.0f;
};

#endif