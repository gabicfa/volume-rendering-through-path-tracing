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