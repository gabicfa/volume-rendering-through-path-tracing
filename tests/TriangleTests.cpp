#include <gtest/gtest.h>
#include "Triangle.h"
#include "Ray.h"
#include "Intersection.h"

TEST(TriangleTest, ConstructingTriangle)
{
    ngl::Vec4 p1(0, 1, 0);
    ngl::Vec4 p2(-1, 0, 0);
    ngl::Vec4 p3(1, 0, 0);

    Triangle t(p1, p2, p3);

    ASSERT_EQ(t.getP1(), p1);
    ASSERT_EQ(t.getP2(), p2);
    ASSERT_EQ(t.getP3(), p3);

    ngl::Vec4 expectedE1(-1, -1, 0);
    ngl::Vec4 expectedE2(1, -1, 0);
    ASSERT_EQ(t.getE1(), expectedE1);
    ASSERT_EQ(t.getE2(), expectedE2);

    ngl::Vec4 expectedNormal(0, 0, -1);
    ASSERT_EQ(t.getNormal(), expectedNormal);
}

TEST(TriangleTest, LocalNormalAt)
{
    Triangle t(ngl::Vec4(0, 1, 0), ngl::Vec4(-1, 0, 0), ngl::Vec4(1, 0, 0));

    ngl::Vec4 n1 = t.localNormalAt(ngl::Vec4(0, 0.5, 0));
    ngl::Vec4 n2 = t.localNormalAt(ngl::Vec4(-0.5, 0.75, 0));
    ngl::Vec4 n3 = t.localNormalAt(ngl::Vec4(0.5, 0.25, 0));

    ASSERT_EQ(n1, t.getNormal());
    ASSERT_EQ(n2, t.getNormal());
    ASSERT_EQ(n3, t.getNormal());
}

TEST(TriangleTest, RayParallelToTriangle)
{
    Triangle t(ngl::Vec4(0, 1, 0), ngl::Vec4(-1, 0, 0), ngl::Vec4(1, 0, 0));
    Ray r(ngl::Vec4(0, -1, -2), ngl::Vec4(0, 1, 0));

    std::vector<Intersection> xs = t.localIntersect(r);

    ASSERT_TRUE(xs.empty());
}

TEST(TriangleTest, RayMissesP1P3Edge)
{
    Triangle t(ngl::Vec4(0, 1, 0), ngl::Vec4(-1, 0, 0), ngl::Vec4(1, 0, 0));
    Ray r(ngl::Vec4(1, 1, -2), ngl::Vec4(0, 0, 1));

    std::vector<Intersection> xs = t.localIntersect(r);

    ASSERT_TRUE(xs.empty());
}

TEST(TriangleTest, RayMissesP1P2Edge)
{
    Triangle t(ngl::Vec4(0, 1, 0), ngl::Vec4(-1, 0, 0), ngl::Vec4(1, 0, 0));
    Ray r(ngl::Vec4(-1, 1, -2), ngl::Vec4(0, 0, 1));

    std::vector<Intersection> xs = t.localIntersect(r);

    ASSERT_TRUE(xs.empty());
}

TEST(TriangleTest, RayMissesP2P3Edge)
{
    Triangle t(ngl::Vec4(0, 1, 0), ngl::Vec4(-1, 0, 0), ngl::Vec4(1, 0, 0));
    Ray r(ngl::Vec4(0, -1, -2), ngl::Vec4(0, 0, 1));

    std::vector<Intersection> xs = t.localIntersect(r);

    ASSERT_TRUE(xs.empty());
}

TEST(TriangleTest, RayStrikesTriangle)
{
    Triangle t(ngl::Vec4(0, 1, 0), ngl::Vec4(-1, 0, 0), ngl::Vec4(1, 0, 0));
    Ray r(ngl::Vec4(0, 0.5, -2), ngl::Vec4(0, 0, 1));

    std::vector<Intersection> xs = t.localIntersect(r);

    ASSERT_EQ(xs.size(), 1);
    ASSERT_FLOAT_EQ(xs[0].t(), 2.0f);
}