#include <gtest/gtest.h>
#include "Transformations.h"

TEST(Transformations, defautlOrientation)
{
    auto from = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto to = ngl::Vec4(0.0f, 0.0f, -1.0f);
    auto up = ngl::Vec4(0.0f, 1.0f, 0.0f);

    auto t = Transformations::viewTransform(from,to,up);
    // ASSERT_EQ(t, ngl::Mat4());
}

TEST(Transformations, transformationViewNegativeZ)
{
    auto from = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto to = ngl::Vec4(0.0f, 0.0f, -1.0f);
    auto up = ngl::Vec4(0.0f, 1.0f, 0.0f);

    auto t = Transformations::viewTransform(from,to,up);
    // ASSERT_EQ(t, ngl::Mat4::scale(-1.0f,1.0f,-1.0f));
}

TEST(Transformations, transformationMovesScene)
{
    auto from = ngl::Vec4(0.0f, 0.0f, -8.0f);
    auto to = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto up = ngl::Vec4(0.0f, 1.0f, 0.0f);

    auto t = Transformations::viewTransform(from,to,up);
    // ASSERT_EQ(t, ngl::Mat4::translate(0.0f,0.0f,8.0f));
}

TEST(Transformations, arbitratyViewTransformation)
{
    auto from = ngl::Vec4(1.0f, 3.0f, -2.0f);
    auto to = ngl::Vec4(4.0f, -2.0f, -8.0f);
    auto up = ngl::Vec4(1.0f, 1.0f, 0.0f);

    auto t = Transformations::viewTransform(from,to,up);
    // ASSERT_EQ(t, ngl::Mat4(-0.50709f, 0.50709f, 0.67612f, -2.36643f,
    //                        0.76772f, 0.60609f, 0.12122f, -2.82843f,
    //                        -0.35857f, 0.59761f, -0.71714f, 0,
    //                        0, 0, 0, 1));
}