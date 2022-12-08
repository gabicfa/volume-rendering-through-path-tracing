#include <gtest/gtest.h>

#include "Canvas.h"

TEST(Canvas, createPixel)
{
    auto c = Canvas();
    auto position = ngl::Vec3(0.0f, 0.0f, 0.0f);
    auto colour = ngl::Vec3(0.0f, 1.0f, 0.0f);
    c.createPixel(position, colour);
    auto p = c.getPixels().front();
    ASSERT_EQ(p.position, position);
    ASSERT_EQ(p.colour, colour);
}