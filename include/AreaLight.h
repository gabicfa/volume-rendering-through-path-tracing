#include <ngl/Vec4.h>
#include <ngl/Vec3.h>

class AreaLight {
public:
    AreaLight(const ngl::Vec4& _center, const ngl::Vec4& _udir, const ngl::Vec4& _vdir, const ngl::Vec3& _intensity);

    ngl::Vec4 udir() const;
    ngl::Vec4 vdir() const;
    ngl::Vec4 center() const;
    ngl::Vec3 intensity() const;

    void sample(ngl::Vec4& _samplePoint, ngl::Vec3& _intensity) const;

private:
    ngl::Vec4 m_center;
    ngl::Vec4 m_udir, m_vdir;
    ngl::Vec3 m_intensity;
};
