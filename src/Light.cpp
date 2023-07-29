#include "Light.h"
#include "Computation.h"
#include "Ray.h"

Light::Light()
{

}

Light::Light(ngl::Vec3 _i, ngl::Vec4 _p) : m_intensity{_i}, m_position{_p}
{

}
ngl::Vec3 Light::intensity() const
{
    return m_intensity;
}

ngl::Vec4 Light::position() const
{
    return m_position;
}

bool Light::operator==(const Light& other) const
{
    return m_intensity == other.intensity() && m_position == other.position();
}

ngl::Vec3 Light::sampleLi(const Computation &ctx, ngl::Vec4 *wi, float *pdf) const
{
    *wi = (m_position - ctx.point).normalize();
    *pdf = 1.f;
    return m_intensity;
}

ngl::Vec3 Light::le(const Ray &ray) const 
{
    return ray.direction().dot(m_position - ray.origin()) > 0 ? m_intensity : ngl::Vec3(0, 0, 0);
}

float Light::pdfLi() const 
{
    return 1.f;
}
