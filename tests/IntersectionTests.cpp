#include <gtest/gtest.h>
#include "Intersection.h"

#include "Sphere.h"

TEST(Intersection, createIntersection)
{
    auto s = Sphere(1);
    auto i = Intersection(3.5f, s.id());
    ASSERT_EQ(i.t(), 3.5f);
    ASSERT_EQ(i.object(), 1);
}

TEST(Intersection, aggregatingIntersections)
{
    auto s = Sphere(1);
    auto i1 = Intersection(1.0f, s.id());
    auto i2 = Intersection(2.0f, s.id());
    auto xs = Intersection::intersections(i1, i2);
    ASSERT_EQ(xs.size(), 2);
    ASSERT_EQ(xs[0].t(), 1.0f);
    ASSERT_EQ(xs[1].t(), 2.0f);
}