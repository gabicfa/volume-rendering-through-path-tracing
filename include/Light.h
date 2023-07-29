#ifndef LIGHT_H_
#define LIGHT_H_
#include <iostream>
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>

class Computation;
class Ray;


class Light
{
    public:
        Light();
        Light(ngl::Vec3 _i, ngl::Vec4 _p);
        ngl::Vec3 intensity() const;
        ngl::Vec4 position() const;
        bool operator==(const Light& other) const;
        ngl::Vec3 sampleLi(const Computation &ctx, ngl::Vec4 *wi, float *pdf) const;
        ngl::Vec3 le(const Ray &ray) const;
        float pdfLi() const;
    private:
        ngl::Vec3 m_intensity;
        ngl::Vec4 m_position;
};
#endif