#include <gtest/gtest.h>
#include "Ray.h"
#include "Sphere.h"

TEST(Sphere, rayIntersectTangent)
{
    auto origin = ngl::Vec3(0.0f,0.0f,5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,-1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), 4.0f);
    ASSERT_EQ(xs[1].t(), 6.0f);
}

TEST(Sphere, missesTheSphere)
{
    auto origin = ngl::Vec3(0.0f,2.0f,5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,-1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(Sphere, rayInsideSphere)
{
    auto origin = ngl::Vec3(0.0f,0.0f,0.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,-1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), -1.0f);
    ASSERT_EQ(xs[1].t(), 1.0f);
}

TEST(Sphere, rayBehindSphere)
{
    auto origin = ngl::Vec3(0.0f,0.0f,-5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,-1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), -6.0f);
    ASSERT_EQ(xs[1].t(), -4.0f);
}

TEST(Sphere, intersectsSetObj)
{
    auto origin = ngl::Vec3(0.0f,0.0f,5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,-1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].object()->id(), 1);
    ASSERT_EQ(xs[1].object()->id(), 1);
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
    auto m = ngl::Mat4::translate(2.0f,3.0f,-4.0f);
    s.setTransform(m);
    ASSERT_EQ(s.transform(), m);
}

TEST(Sphere, intersectsScaledSphere)
{
    auto origin = ngl::Vec3(0.0f,0.0f,5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,-1.0f);
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
    auto origin = ngl::Vec3(0.0f,0.0f,5.0f);
    auto direction = ngl::Vec3(0.0f,0.0f,-1.0f);
    auto r = Ray(origin, direction);

    auto s = Sphere(1);
    auto m = ngl::Mat4::translate(5.0f,0.0f,0.0f);
    s.setTransform(m);

    auto xs = s.intersect(r);
    ASSERT_EQ(xs.size(), 0);
}

TEST(Sphere, normalAtXaxis)
{
    auto s = Sphere(1);
    auto n = s.normalAt(ngl::Vec4(1.0f,0.0f,0.0f));
    ASSERT_EQ(n, ngl::Vec3(1.0f,0.0f,0.0f));
}

TEST(Sphere, normalAtYaxis)
{
    auto s = Sphere(1);
    auto n = s.normalAt(ngl::Vec4(0.0f,1.0f,0.0f));
    ASSERT_EQ(n, ngl::Vec3(0.0f,1.0f,0.0f));
}

TEST(Sphere, normalAtZaxis)
{
    auto s = Sphere(1);
    auto n = s.normalAt(ngl::Vec4(0.0f,0.0f,-1.0f));
    ASSERT_EQ(n, ngl::Vec4(0.0f,0.0f,-1.0f));
}

TEST(Sphere, normalAtNonaxialPoint)
{
    auto s = Sphere(1);
    auto p = std::sqrt(3)/3;
    auto n = s.normalAt(ngl::Vec4(p,p,p));
    ASSERT_EQ(n, ngl::Vec3(p,p,p));
}

TEST(Sphere, normalIsANormalizedVector)
{
    auto s = Sphere(1);
    auto p = std::sqrt(3)/3;
    auto v = ngl::Vec4(p,p,p);
    auto n = s.normalAt(v);
    ASSERT_EQ(n, v.normalize());
}

TEST(Sphere, normalOnTranslatedSphere)
{
    auto s = Sphere(1);
    auto m = ngl::Mat4::translate(0.0f,1.0f,0.0f);
    s.setTransform(m);
    auto n = s.normalAt(ngl::Vec4(0, 1.70711, 0.70711));
    ASSERT_EQ(n, ngl::Vec4(0, 0.70711, 0.70711));
}

TEST(Sphere, normalOnTransformedSphere)
{
    auto s = Sphere(1);
    auto m = ngl::Mat4::scale(1.0f,0.5f,1.0f) * ngl::Mat4::rotateZ(M_PI/5);
    s.setTransform(m);
    auto n = s.normalAt(ngl::Vec4(0, (std::sqrt(2)/2), (std::sqrt(2)/2)));
    ASSERT_EQ(n, ngl::Vec4(0, 0.97014, 0.24254));
}

TEST(Sphere, defaultMaterial)
{
    auto s = Sphere(1);
    auto m = s.material();
    ASSERT_EQ(m, Material());
}

TEST(Sphere, assignMaterial)
{
    auto s = Sphere(1);
    auto m = Material();
    m.ambient(1.0f);
    s.setMaterial(m);
    ASSERT_EQ(s.material(), m);
}