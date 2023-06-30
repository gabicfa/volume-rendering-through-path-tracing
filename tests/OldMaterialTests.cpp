#include <gtest/gtest.h>
#include "OldMaterial.h"

TEST(OldMaterial, defaultMaterial)
{
    auto m = OldMaterial();
    ASSERT_EQ(m.color(), ngl::Vec3(1.0f,1.0f,1.0f));
    ASSERT_EQ(m.ambient(), 0.1f);
    ASSERT_EQ(m.diffuse(), 0.9f);
    ASSERT_EQ(m.specular(), 0.9f);
    ASSERT_EQ(m.shininess(), 200.0f);
}

TEST(OldMaterial, lightiningEyeBetweenLightAndSurface)
{
    auto m = OldMaterial();
    auto pos = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto eye = ngl::Vec4(0.0f,0.0f, 1.0f);
    auto normal = ngl::Vec4(0.0f,0.0f, 1.0f);
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.0f,10.0f));
    auto result = m.lighting(light, pos, eye, normal);
    ASSERT_EQ(result, ngl::Vec3(1.9f,1.9f,1.9f));
}

TEST(OldMaterial, lightiningEyeOffset45)
{
    auto m = OldMaterial();
    auto pos = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto eye = ngl::Vec4(0.0f,std::sqrt(2)/2, std::sqrt(2)/2);
    auto normal = ngl::Vec4(0.0f,0.0f,1.0f);
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.0f,10.0f));
    auto result = m.lighting(light, pos, eye, normal);
    ASSERT_EQ(result, ngl::Vec3(1.0f,1.0f,1.0f));
}

TEST(OldMaterial, lightiningLightOffset45)
{
    auto m = OldMaterial();
    auto pos = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto eye = ngl::Vec4(0.0f,0.0f,1.0f);
    auto normal = ngl::Vec4(0.0f,0.0f,1.0f);
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,10.0f,10.0f));
    auto result = m.lighting(light, pos, eye, normal);
    ASSERT_EQ(result, ngl::Vec3(0.7364f, 0.7364f, 0.7364f));
}

TEST(OldMaterial, lightiningEyePathReflaction)
{
    auto m = OldMaterial();
    auto pos = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto eye = ngl::Vec4(0.0f,-std::sqrt(2)/2,std::sqrt(2)/2);
    auto normal = ngl::Vec4(0.0f,0.0f,1.0f);
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,10.0f,10.0f));
    auto result = m.lighting(light, pos, eye, normal);
    ASSERT_EQ(result, ngl::Vec3(1.6364f, 1.6364f, 1.6364f));
}

TEST(OldMaterial, lightiningLightBehind)
{
    auto m = OldMaterial();
    auto pos = ngl::Vec4(0.0f, 0.0f, 0.0f);
    auto eye = ngl::Vec4(0.0f,0.0f, 1.0f);
    auto normal = ngl::Vec4(0.0f,0.0f, 1.0f);
    auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.0f, -10.0f));
    auto result = m.lighting(light, pos, eye, normal);
    ASSERT_EQ(result, ngl::Vec3(0.1f, 0.1f, 0.1f));
}