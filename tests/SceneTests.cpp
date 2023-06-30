#include <gtest/gtest.h>
#include "Scene.h"
#include "Intersection.h"
#include "Sphere.h"
TEST(Scene, createScene)
{
    auto scene = Scene();
    auto light = Light();
    ASSERT_EQ(scene.objects().size(), 0);
    ASSERT_EQ(scene.light(), light);
}

TEST(Scene, createDefaultScene)
{
    auto scene = Scene(true);
    auto l = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(-10.0f, 10.0f, 10.0f));
    ASSERT_EQ(scene.light(), l);
    auto s1 = Sphere(1);
    auto mColor = ngl::Vec3(0.8f,1.0f,0.6f);
    auto m = OldMaterial();
    m.color(mColor);
    m.diffuse(0.7);
    m.specular(0.2);
    s1.setOldMaterial(m);

    auto s2 = Sphere(2);
    auto transform = ngl::Mat4::scale(0.5f,0.5f,0.5f);
    s2.setTransform(transform);

    ASSERT_TRUE(std::any_of(scene.objects().begin(), scene.objects().end(),
        [&s1](const std::shared_ptr<Shape>& shape) { return *shape == s1; }));
    ASSERT_TRUE(std::any_of(scene.objects().begin(), scene.objects().end(),
        [&s2](const std::shared_ptr<Shape>& shape) { return *shape == s2; }));
}

TEST(Scene, intersectScene)
{
    auto s = Scene(true);
    auto r = Ray(ngl::Vec4(0.0f, 0.0f, 5.0f), ngl::Vec4(0.0f,0.0f,-1.0f));
    auto xs = s.intersectScene(r);

    ASSERT_EQ(xs.size(), 4);
    ASSERT_EQ(xs[0].t(), 4);
    ASSERT_EQ(xs[1].t(), 4.5);
    ASSERT_EQ(xs[2].t(), 5.5);
    ASSERT_EQ(xs[3].t(), 6);
}

TEST(Scene, shadingIntersection)
{
    auto s = Scene(true);
    auto r = Ray(ngl::Vec4(0.0f, 0.0f, 5.0f), ngl::Vec4(0.0f,0.0f,-1.0f));
    auto s1 = std::dynamic_pointer_cast<Sphere>(s.objects()[0]);
    auto i = Intersection(4.0f, s1);

    auto comp = i.prepareComputations(r);
    auto color = s.shadeHit(comp);

    ASSERT_EQ(color, ngl::Vec3(0.38066f, 0.47583f, 0.2855f));
}

TEST(Scene, shadingIntersectionFromInside)
{
    auto s = Scene(true);
    auto l = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.25f,0.0f));
    s.light(l);
    auto r = Ray(ngl::Vec4(0.0f, 0.0f, 0.0f), ngl::Vec4(0.0f,0.0f,1.0f));
    
    auto s2 = std::dynamic_pointer_cast<Sphere>(s.objects()[1]);
    auto i = Intersection(0.5f, s2);

    auto comp = i.prepareComputations(r);
    auto color = s.shadeHit(comp);

    ASSERT_EQ(color, ngl::Vec3(0.90498f, 0.90498f, 0.90498f));
}

TEST(Scene, colorWhenRayMisses)
{
    auto s = Scene(true);
    auto r = Ray(ngl::Vec4(0.0f, 0.0f, 5.0f), ngl::Vec4(0.0f,1.0f,0.0f));
    auto color = s.colorAt(r, 1);

    auto d = r.direction()/r.direction().length();
    auto t = 0.5 * (d.m_y + 1.0);
    auto c = (1.0-t)*ngl::Vec3(1.0, 1.0, 1.0) + t*ngl::Vec3(0.5, 0.7, 1.0);    

    ASSERT_EQ(color, c);
}

TEST(Scene, colorWhenRayHits)
{
    auto s = Scene(true);
    auto r = Ray(ngl::Vec4(0.0f, 0.0f, 5.0f), ngl::Vec4(0.0f,0.0f,-1.0f));
    auto color = s.colorAt(r, 1);
    
    ASSERT_EQ(color, ngl::Vec3(0.38066f, 0.47583f, 0.2855f));
}

TEST(Scene, colorWithIntersectionBehindRay)
{
    auto s = Scene(true);
    auto outer = std::dynamic_pointer_cast<Sphere>(s.objects()[0]);
    auto m1 = outer->oldMaterial();
    m1.ambient(1.0f);
    outer->setOldMaterial(m1);

    auto inner = std::dynamic_pointer_cast<Sphere>(s.objects()[1]);
    auto m2 = inner->oldMaterial();
    m2.ambient(1.0f);
    inner->setOldMaterial(m2);

    auto r = Ray(ngl::Vec4(0.0f, 0.0f, -0.75f), ngl::Vec4(0.0f,0.0f,1.0f));
    auto color = s.colorAt(r, 1);
    ASSERT_EQ(color, inner->oldMaterial().color());
}



