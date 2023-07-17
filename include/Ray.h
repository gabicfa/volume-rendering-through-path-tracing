#ifndef RAY_H_
#define RAY_H_
#include <ngl/Vec4.h>
#include <ngl/Mat4.h>

class Ray
{
    public:
        Ray() = default;
        Ray(ngl::Vec4 _origin, ngl::Vec4 _direction);
        ngl::Vec4 origin() const;
        ngl::Vec4 direction() const;
        ngl::Vec4 position(float _t);
        Ray transform(ngl::Mat4 _tMatrix);
    private:
        ngl::Vec4 m_origin;
        ngl::Vec4 m_direction;

};

#endif