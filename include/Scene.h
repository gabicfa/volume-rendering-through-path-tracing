#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <vector>
#include "Sphere.h"
#include "Light.h"
#include "Computation.h"
#include <ngl/Vec3.h>

class Scene
{
    public:
        Scene(bool _default = false);
        std::vector<Sphere> objects();
        Light light() const;
        void light(Light _l);
        void addObject(Sphere s);
        std::vector<Intersection> intersectScene(Ray _r);
        ngl::Vec3 shadeHit(Computation _c);
        ngl::Vec3 colorAt(Ray _r);
    private:
        std::vector<Sphere> m_objects;
        Light m_light;

};
#endif