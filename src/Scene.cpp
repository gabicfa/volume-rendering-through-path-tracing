#include "Scene.h"
#include<ngl/Vec3.h>
#include<ngl/Vec4.h>

Scene::Scene(bool _default)
{
    if(_default) 
    {
        auto lPoint = ngl::Vec4(-10.0f, 10.0f, -10.0f);
        auto lIntensity = ngl::Vec3(1.0f,1.0f,1.0f);
        auto l = Light(lIntensity,lPoint);
        m_light = l;

        auto s1 = Sphere(1);
        auto mColor = ngl::Vec3(0.8f,1.0f,0.6f);
        auto m = Material();
        m.color(mColor);
        m.diffuse(0.7);
        m.specular(0.2);
        m_objects.push_back(s1);

        auto s2 = Sphere(2);
        auto transform = ngl::Mat4::scale(0.5f,0.5f,0.5f);
        s2.setTransform(transform);
        m_objects.push_back(s2);
    }
}

std::vector<Sphere> Scene::objects()
{
    return m_objects;
}

Light Scene::light()
{
    return m_light;
}

std::vector<Intersection> Scene::intersectScene(Ray _r)
{
    std::vector<Intersection> intersections;
    for (Sphere &o : m_objects) 
    {
        auto inter = o.intersect(_r);
        for(auto &i: inter)
            intersections.push_back(i);
    }
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    return intersections;
}