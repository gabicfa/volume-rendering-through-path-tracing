#include "Scene.h"
#include<ngl/Vec3.h>
#include<ngl/Vec4.h>
#include "Triangle.h"

Scene::Scene(bool _default)
{
    if(_default) 
    {
        auto lPoint = ngl::Vec4(-10.0f, 10.0f, 10.0f);
        auto lIntensity = ngl::Vec3(1.0f,1.0f,1.0f);
        auto l = Light(lIntensity,lPoint);
        m_light = l;

        auto t1 = std::make_shared<Triangle>(ngl::Vec4(0, 1, 0), ngl::Vec4(-1, 0, 0), ngl::Vec4(1, 0, 0));

        auto mColor = ngl::Vec3(0.8f,1.0f,0.6f);
        auto m = Material();
        m.color(mColor);
        m.diffuse(0.7);
        m.specular(0.2);
        t1->setMaterial(m);
        m_objects.push_back(t1);

        auto s2 = std::make_shared<Sphere>(2);
        auto transform = ngl::Mat4::scale(0.5f,0.5f,0.5f);
        s2->setTransform(transform);
        // m_objects.push_back(s2);
    }
}

std::vector<std::shared_ptr<Shape>>& Scene::objects()
{
    return m_objects;
}

Light Scene::light() const
{
    return m_light;
}

void Scene::light(Light _l)
{
    m_light = _l;
}

void Scene::addObject(std::shared_ptr<Shape> s)
{
    m_objects.push_back(s);
}

std::vector<Intersection> Scene::intersectScene(Ray _r)
{
    std::vector<Intersection> intersections;
    for (const auto& o : m_objects)
    {
        auto inter = o->intersect(_r);
        for(auto &i: inter)
            intersections.push_back(i);
    }
    std::sort(intersections.begin(), intersections.end(), [](const Intersection &a, const Intersection &b) 
    {
        return a.t() < b.t();
    });
    return intersections;
}

ngl::Vec3 Scene::shadeHit(Computation _c)
{
    auto m =  _c.object->material();
    return m.lighting(this->light(), _c.point, _c.eye, _c.normal);
}

ngl::Vec3 Scene::colorAt(Ray _r)
{
    auto intersections = this->intersectScene(_r);
    auto xs = Intersection::intersections(intersections);
    auto i = Intersection::hit(xs);

    Intersection empty = Intersection();
    if (i == empty)
    {
        auto d = _r.direction()/_r.direction().length();
        auto t = 0.5 * (d.m_y + 1.0);
        auto color = (1.0-t)*ngl::Vec3(1.0, 1.0, 1.0) + t*ngl::Vec3(0.5, 0.7, 1.0);    
        return color;
    }
    else
    {
        auto c = i.prepareComputations(_r);
        return shadeHit(c);
    }
}