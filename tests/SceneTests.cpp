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



