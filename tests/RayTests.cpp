#include <gtest/gtest.h>
#include "Ray.h"
#include <ngl/Transformation.h>

TEST(Ray, createRay)
{
    auto origin = ngl::Vec4(1.0f,2.0f,3.0f);
    auto direction = ngl::Vec4(4.0f,5.0f,6.0f);
    auto r = Ray(origin, direction);
    ASSERT_EQ(r.direction(), direction);
    ASSERT_EQ(r.origin(), origin);
}

TEST(Ray, raysPosition)
{
    auto origin = ngl::Vec4(2.0f,3.0f,4.0f);
    auto direction = ngl::Vec4(1.0f,0.0f,0.0f);
    auto r = Ray(origin, direction);
    ASSERT_EQ(r.position(0), ngl::Vec4(2.0f,3.0f,4.0f));
    ASSERT_EQ(r.position(1), ngl::Vec4(3.0f,3.0f,4.0f));
    ASSERT_EQ(r.position(-1), ngl::Vec4(1.0f,3.0f,4.0f));
    ASSERT_EQ(r.position(2.5), ngl::Vec4(4.5f,3.0f,4.0f));
}

TEST(Ray, translateRay)
{
    auto origin = ngl::Vec4(1.0f,2.0f,3.0f);
    auto direction = ngl::Vec4(0.0f,1.0f,0.0f);
    auto r = Ray(origin, direction);
    auto m = ngl::Mat4::translate(3.0f,4.0f,5.0f);
    auto newRay = r.transform(m);
    ASSERT_EQ(newRay.origin(), ngl::Vec4(4.0f,6.0f,8.0f));
    ASSERT_EQ(newRay.direction(), ngl::Vec4(0.0f,1.0f,0.0f));
}

TEST(Ray, scalingRay)
{
    auto origin = ngl::Vec4(1.0f,2.0f,3.0f);
    auto direction = ngl::Vec4(0.0f,1.0f,0.0f);
    auto r = Ray(origin, direction);
    auto m = ngl::Mat4::scale(2.0f,3.0f,4.0f);
    auto newRay = r.transform(m);
    ASSERT_EQ(newRay.origin(), ngl::Vec4(2.0f,6.0f,12.0f));
    ASSERT_EQ(newRay.direction(), ngl::Vec4(0.0f,3.0f,0.0f));
}