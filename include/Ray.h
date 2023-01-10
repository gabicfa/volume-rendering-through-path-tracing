#ifndef RAY_H_
#define RAY_H_
#include <ngl/Vec3.h>

class Ray
{
    public:
        Ray(ngl::Vec3 _origin, ngl::Vec3 _direction);
        ngl::Vec3 origin() const;
        ngl::Vec3 direction() const;
        ngl::Vec3 position(float _t);
    private:
        ngl::Vec3 m_origin;
        ngl::Vec3 m_direction;

};

#endif