#include <gtest/gtest.h>
#include "Intersection.h"

#include "Sphere.h"
#include "Ray.h"

TEST(Intersection, createIntersection)
{
    auto s = Sphere(1);
    auto i = Intersection(3.5f, &s);
    ASSERT_EQ(i.t(), 3.5f);
    ASSERT_EQ(i.object(), 1);
}

TEST(Intersection, aggregatingIntersections)
{
    auto s = Sphere(1);
    auto i1 = Intersection(1.0f, &s);
    auto i2 = Intersection(2.0f, &s);
    std::vector<Intersection> all_intersections = {i1, i2};
    auto xs = Intersection::intersections(all_intersections);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), 1.0f);
    ASSERT_EQ(xs[1].t(), 2.0f);
}

TEST(Intersection, hitAllIntersectionsPositiveT)
{
    auto s = Sphere(1);
    auto i1 = Intersection(1.0f, &s);
    auto i2 = Intersection(2.0f, &s);
    std::vector<Intersection> all_intersections = {i2, i1};
    auto xs = Intersection::intersections(all_intersections);
    auto i = Intersection::hit(xs);
    ASSERT_EQ(i, i1);
}

TEST(Intersection, hitIntersectionsSomeNegT)
{
    auto s = Sphere(1);
    auto i1 = Intersection(-1.0f, &s);
    auto i2 = Intersection(1.0f, &s);
    std::vector<Intersection> all_intersections = {i2, i1};
    auto xs = Intersection::intersections(all_intersections);
    auto i = Intersection::hit(xs);
    ASSERT_EQ(i, i2);
}

TEST(Intersection, hitIntersectionsNegT)
{
    auto s = Sphere(1);
    auto i1 = Intersection(-2.0f, &s);
    auto i2 = Intersection(-1.0f, &s);
    std::vector<Intersection> all_intersections = {i2, i1};
    auto xs = Intersection::intersections(all_intersections);
    auto i = Intersection::hit(xs);
    Intersection empty = Intersection();
    ASSERT_EQ(i, empty);
}

TEST(Intersection, hitLowestNonNeg)
{
    auto s = Sphere(1);
    auto i1 = Intersection(5.0f, &s);
    auto i2 = Intersection(7.0f, &s);
    auto i3 = Intersection(-3.0f, &s);
    auto i4 = Intersection(2.0f, &s);
    std::vector<Intersection> all_intersections = {i1, i2, i3, i4};
    auto xs = Intersection::intersections(all_intersections);
    auto i = Intersection::hit(xs);
    ASSERT_EQ(i, i4);
}

TEST(Intersection, preCompStateOfIntersection)
{
    auto r = Ray(ngl::Vec4(0.0f,0.0f,-5.0f), ngl::Vec4(0.0f,0.0f,1.0f));
    auto s = Sphere(1);
    auto i = Intersection(4.0f, &s);

    auto comp = i.prepareComputations(r);

    ASSERT_EQ(comp.t, i.t());
    ASSERT_EQ(comp.point, ngl::Vec4(0.0f,0.0f,-1.0f));
    ASSERT_EQ(comp.eye, ngl::Vec4(0.0f,0.0f,-1.0f));
    ASSERT_EQ(comp.normal, ngl::Vec4(0.0f,0.0f,-1.0f));

}

TEST(Intersection, hitWhenIntersectionOutside)
{
    auto r = Ray(ngl::Vec4(0.0f,0.0f,-5.0f), ngl::Vec4(0.0f,0.0f,1.0f));
    auto s = Sphere(1);
    auto i = Intersection(4.0f, &s);

    auto comp = i.prepareComputations(r);

    ASSERT_EQ(comp.inside, false);
}

TEST(Intersection, hitWhenIntersectionInside)
{
    auto r = Ray(ngl::Vec4(0.0f,0.0f,0.0f), ngl::Vec4(0.0f,0.0f,1.0f));
    auto s = Sphere(1);
    auto i = Intersection(1.0f, &s);

    auto comp = i.prepareComputations(r);

    ASSERT_EQ(comp.point, ngl::Vec4(0.0f,0.0f,1.0f));
    ASSERT_EQ(comp.eye, ngl::Vec4(0.0f,0.0f,-1.0f));
    ASSERT_EQ(comp.inside, true);
    ASSERT_EQ(comp.normal, ngl::Vec4(0.0f,0.0f,-1.0f));

}