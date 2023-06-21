#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <vector>
#include "Sphere.h"
#include "Shape.h"
#include "Light.h"
#include "Computation.h"
#include <ngl/Vec3.h>

class Scene
{
    public:
        Scene(bool _default = false);
        std::vector<std::shared_ptr<Shape>>& objects();
        Light light() const;
        void light(Light _l);
        void addObject(std::shared_ptr<Shape> s);
        std::vector<Intersection> intersectScene(Ray _r);
        ngl::Vec3 shadeHit(Computation _c);
        ngl::Vec3 colorAt(Ray _r);
    private:
        std::vector<std::shared_ptr<Shape>> m_objects;
        Light m_light;

};
#endif