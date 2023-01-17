#ifndef SCENE_H_
#define SCENE_H_
#include <iostream>
#include <vector>
#include "Sphere.h"
#include "Light.h"
class Scene
{
    public:
        Scene(bool _default = false);
        std::vector<Sphere> objects();
        Light light();
        std::vector<Intersection> intersectScene(Ray _r);
    private:
        std::vector<Sphere> m_objects;
        Light m_light;

};
#endif