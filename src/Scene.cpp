#include "Scene.h"
#include <ngl/Vec3.h>
#include <ngl/Vec4.h>
#include "Triangle.h"
#include "ObjFile.h"
#include "Sphere.h"
#include "Utility.h"
#include "Lambertian.h"
#include "Metal.h"
#include <memory>

Scene::Scene(bool _default)
{
    if(_default) 
    {
        auto lPoint = ngl::Vec4(-10.0f, 10.0f, 10.0f);
        auto lIntensity = ngl::Vec3(1.0f,1.0f,1.0f);
        auto l = Light(lIntensity,lPoint);
        m_light = l;

        auto s1 = std::make_shared<Sphere>(1);
        auto mColor = ngl::Vec3(0.8f,1.0f,0.6f);
        auto m = OldMaterial();
        m.color(mColor);
        m.diffuse(0.7);
        m.specular(0.2);
        s1->setOldMaterial(m);
        m_objects.push_back(s1);

        auto s2 = std::make_shared<Sphere>(2);
        auto transform = ngl::Mat4::scale(0.5f,0.5f,0.5f);
        s2->setTransform(transform);
        m_objects.push_back(s2);
    }

}

Scene::Scene(bool _default, int num)
{
        auto lPoint = ngl::Vec4(-10.0f, 10.0f, 10.0f);
        auto lIntensity = ngl::Vec3(1.0f,1.0f,1.0f);
        auto l = Light(lIntensity,lPoint);
        m_light = l;

        auto materialGround = std::make_shared<Lambertian>(ngl::Vec4(0.8, 0.8, 0.0));
        auto materialCenter = std::make_shared<Lambertian>(ngl::Vec4(0.7, 0.3, 0.3));
        auto materialLeft   = std::make_shared<Metal>(ngl::Vec4(0.8, 0.8, 0.8));
        auto materialRight  = std::make_shared<Metal>(ngl::Vec4(0.8, 0.6, 0.2));

        ObjFile obj1("files/Pyramid.obj");
        auto g1 = obj1.defaultGroup();
        for (auto t=0; t < g1->getChildren().size(); t ++)
        {
            auto triangle = std::dynamic_pointer_cast<Triangle>(g1->getChildren()[t]);
            triangle->setMaterial(materialRight);
            triangle->setTransform(ngl::Mat4::translate(0.7, -0.5, -1.5));
            triangle->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
            // m_objects.push_back(triangle);
        }
        
        ObjFile obj2("files/Pyramid.obj");
        auto g2 = obj2.defaultGroup();
        for (auto t=0; t < g2->getChildren().size(); t ++)
        {
            auto triangle = std::dynamic_pointer_cast<Triangle>(g2->getChildren()[t]);
            triangle->setMaterial(materialLeft);
            triangle->setTransform(ngl::Mat4::translate(-0.7, -0.5, -1.5));
            triangle->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
            m_objects.push_back(triangle);
        }

        ObjFile obj3("files/Teapot.obj");
        auto g3 = obj3.defaultGroup();
        for (auto t=0; t < g3->getChildren().size(); t ++)
        {
            auto triangle = std::dynamic_pointer_cast<Triangle>(g3->getChildren()[t]);
            triangle->setMaterial(materialCenter);
            // triangle->setTransform(ngl::Mat4::translate(-0.7, -0.5, -1.5));
            // triangle->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
        }
        // m_objects.push_back(g3);

        auto s1 = std::make_shared<Sphere>(1, materialGround);
        auto s2 = std::make_shared<Sphere>(2, materialCenter);
        auto s3 = std::dynamic_pointer_cast<Triangle>(g3->getChildren()[1]);
        s3->setMaterial(materialCenter);
        // auto s4 = std::make_shared<Sphere>(4, materialRight);

        s1->setTransform(ngl::Mat4::translate(0.0, -100.5, -1.0));
        s1->setTransform(ngl::Mat4::scale(100.0f, 100.0f, 100.0f));
        // m_objects.push_back(s1);

        s2->setTransform(ngl::Mat4::translate(0.0, 0.0, -1.0));
        s2->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
        // m_objects.push_back(s2);

        // s3->setTransform(ngl::Mat4::translate(-1.0, 0.0, -1.0));
        // s3->setTransform(ngl::Mat4::scale(0.5f, 0.5f, 0.5f));
        m_objects.push_back(s3);

        // s4->setTransform(ngl::Mat4::translate(1.0f, 0.0f, -1.0f));
        // s4->setTransform(ngl::Mat4::scale(0.5, 0.5, 0.5));
        // m_objects.push_back(s4);
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
    auto m =  _c.object->oldMaterial();
    return m.lighting(this->light(), _c.point, _c.eye, _c.normal);
}

ngl::Vec3 Scene::colorAt(Ray _r, int depth)
{
    // If we've exceeded the ray bounce limit, no more light is gathered.
    if (depth <= 0)
        return ngl::Vec3(0,0,0);
    
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

        Ray scattered;
        ngl::Vec3 attenuation;
        if (c.matPtr && c.matPtr->scatter(_r, c, attenuation, scattered))
            return attenuation * colorAt(scattered, depth-1);
        return ngl::Vec3(0.0f,0.0f,0.0f);
        // return shadeHit(c);
    }
}