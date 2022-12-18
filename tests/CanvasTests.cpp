#include <gtest/gtest.h>
#include "Canvas.h"

TEST(Canvas, createCanvas)
{
    auto width = 10;
    auto height = 20;
    auto c = Canvas(width, height);
    ASSERT_EQ(c.width(), width);
    ASSERT_EQ(c.height(), height);
    for(size_t i=0; i<height; ++i)
    {
        for(size_t j=0; j<width; ++j)
        {
             ASSERT_EQ(c.getPixel(i,j),ngl::Vec3(0.0f, 0.0f, 0.0f));
        }
    }
}

TEST(Canvas, writeToCanvas)
{
    auto canvas = Canvas(10, 20);
    auto colour = ngl::Vec3(1.0f,0.0f,1.0f);
    canvas.setPixel(2,3,colour);
    ASSERT_EQ(canvas.getPixel(2,3), colour);
}