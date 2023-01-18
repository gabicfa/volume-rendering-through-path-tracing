#include <gtest/gtest.h>
#include "Camera.h"

TEST(Camera, createCamera)
{
    auto hsize = 160;
    auto vsize = 120;
    auto fieldOfView = M_PI/2;
    auto c = Camera(hsize, vsize, fieldOfView);
    ASSERT_EQ(c.hsize(), 160);
    ASSERT_EQ(c.vsize(), 120);
    ASSERT_EQ(c.fieldOfView(), M_PI/2);
    ASSERT_EQ(c.transform(), ngl::Mat4());
}

TEST(Camera, horizontalCanvasPixelSize)
{
    auto hsize = 200;
    auto vsize = 125;
    auto fieldOfView = M_PI/2;
    auto c = Camera(hsize, vsize, fieldOfView);
    ASSERT_EQ(c.pixelSize(), 0.01f);
}

TEST(Camera, verticalCanvasPixelSize)
{
    auto hsize = 125;
    auto vsize = 200;
    auto fieldOfView = M_PI/2;
    auto c = Camera(hsize, vsize, fieldOfView);
    ASSERT_EQ(c.pixelSize(), 0.01f);
}

TEST(Camera, rayThroughCenterCanvas)
{
    auto c = Camera(201,101,M_PI/2);
    auto r = c.rayForPixel(100,50);
    ASSERT_EQ(r.origin(), ngl::Vec4(0.0f,0.0f,0.0f));
    ASSERT_EQ(r.direction(), ngl::Vec4(0.0f,0.0f,-1.0f));
}

TEST(Camera, rayThroughCornerCanvas)
{
    auto c = Camera(201,101,M_PI/2);
    auto r = c.rayForPixel(0,0);
    ASSERT_EQ(r.origin(), ngl::Vec4(0.0f,0.0f,0.0f));
    ASSERT_EQ(r.direction(), ngl::Vec4(0.66519f, 0.33259f, -0.66851f));
}

TEST(Camera, rayCameraTransformed)
{
    auto c = Camera(201,101,M_PI/2);
    auto matTrans = ngl::Mat4::rotateY(M_PI/4) * ngl::Mat4::translate(0.0f, -2.0f, 5.0f);
    c.transform(matTrans);
    auto r = c.rayForPixel(100,50);
    ASSERT_EQ(r.origin(), ngl::Vec4(0.0f,2.0f,-5.0f));
    // ASSERT_EQ(r.direction(), ngl::Vec4(std::sqrt(2)/2, 0.0f, -std::sqrt(2)/2));
}

TEST(Camera, renderingSceneWithCamera)
{
    auto scene = Scene(true);
    auto c = Camera(11,11,M_PI/2);
    auto from = ngl::Vec4(0.0f,0.0f,-5.0f);
    auto to = ngl::Vec4(0.0f,0.0f,0.0f);
    auto down = ngl::Vec4(0.0f,1.0f,0.0f);
    auto matTrans = Transformations::viewTransform(from, to, down);
    c.transform(matTrans);
    auto img = c.render(scene);
    // ASSERT_EQ(img.getPixel(5,5), ngl::Vec3(0.38066f, 0.47583f, 0.2855f));
}