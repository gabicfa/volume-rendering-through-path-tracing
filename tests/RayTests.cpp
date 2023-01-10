#include <gtest/gtest.h>
#include "Ray.h"

TEST(Ray, createRay)
{
    auto origin = ngl::Vec3(1.0f,2.0f,3.0f);
    auto direction = ngl::Vec3(4.0f,5.0f,6.0f);
    auto r = Ray(origin, direction);
    ASSERT_EQ(r.direction(), direction);
    ASSERT_EQ(r.origin(), origin);
}

TEST(Ray, raysPosition)
{
    auto origin = ngl::Vec3(2.0f,3.0f,4.0f);
    auto direction = ngl::Vec3(1.0f,0.0f,0.0f);
    auto r = Ray(origin, direction);
    ASSERT_EQ(r.position(0), ngl::Vec3(2.0f,3.0f,4.0f));
    ASSERT_EQ(r.position(1), ngl::Vec3(3.0f,3.0f,4.0f));
    ASSERT_EQ(r.position(-1), ngl::Vec3(1.0f,3.0f,4.0f));
    ASSERT_EQ(r.position(2.5), ngl::Vec3(4.5f,3.0f,4.0f));
}