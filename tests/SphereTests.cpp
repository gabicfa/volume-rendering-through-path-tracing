#include <gtest/gtest.h>
#include "Ray.h"
#include "Sphere.h"

TEST(Sphere, rayIntersectTangent)
{
    auto origin = ngl::Vec3(0.0f,0.0f,-5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), 4.0f);
    ASSERT_EQ(xs[1].t(), 6.0f);
}

TEST(Sphere, missesTheSphere)
{
    auto origin = ngl::Vec3(0.0f,2.0f,-5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(Sphere, rayInsideSphere)
{
    auto origin = ngl::Vec3(0.0f,0.0f,0.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), -1.0f);
    ASSERT_EQ(xs[1].t(), 1.0f);
}

TEST(Sphere, rayBehindSphere)
{
    auto origin = ngl::Vec3(0.0f,0.0f,5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), -6.0f);
    ASSERT_EQ(xs[1].t(), -4.0f);
}

TEST(Sphere, intersectsSetObj)
{
    auto origin = ngl::Vec3(0.0f,0.0f,-5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].object(), 1);
    ASSERT_EQ(xs[1].object(), 1);
}

TEST(Sphere, defaultTransformation)
{
    auto s = Sphere(1);
    ngl::Mat4 identity;
    identity.identity();
    ASSERT_EQ(s.transform(), identity);
}

TEST(Sphere, changingTransformation)
{
    auto s = Sphere(1);
    auto m = ngl::Mat4::translate(2.0f,3.0f,4.0f);
    s.setTransform(m);
    ASSERT_EQ(s.transform(), m);
}

TEST(Sphere, intersectsScaledSphere)
{
    auto origin = ngl::Vec3(0.0f,0.0f,-5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto m = ngl::Mat4::scale(2.0f,2.0f,2.0f);
    s.setTransform(m);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), 3.0f);
    ASSERT_EQ(xs[1].t(), 7.0f);
}

TEST(Sphere, intersectsTranslatedSphere)
{
    auto origin = ngl::Vec3(0.0f,0.0f,-5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto m = ngl::Mat4::translate(5.0f,0.0f,0.0f);
    s.setTransform(m);

    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}