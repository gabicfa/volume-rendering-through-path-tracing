#include <gtest/gtest.h>
#include "Light.h"

TEST(Light, createLight)
{
    auto intensity = ngl::Vec3(1.0f,1.0f,1.0f);
    auto position = ngl::Vec4(0.0f,0.0f,0.0f);
    auto light = Light(intensity, position);
    ASSERT_EQ(light.intensity(), intensity);
    ASSERT_EQ(light.position(), position);
}