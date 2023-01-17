#include <gtest/gtest.h>
#include "Material.h"

TEST(Material, defaultMaterial)
{
    auto m = Material();
    ASSERT_EQ(m.color(), ngl::Vec3(1.0f,1.0f,1.0f));
    ASSERT_EQ(m.ambient(), 0.1f);
    ASSERT_EQ(m.diffuse(), 0.9f);
    ASSERT_EQ(m.specular(), 0.9f);
    ASSERT_EQ(m.shininess(), 200.0f);
}

TEST(Material, lightining)
{
    auto m = Material();
    auto pos = ngl::Vec4(0.0f, 0.0f, 0.0f);
    {
        // Eye between light and surface
        auto eye = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto normal = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.0f,-10.0f));
        auto result = m.lighting(light, pos, eye, normal);
        ASSERT_EQ(result, ngl::Vec3(1.0f,1.0f,1.0f));
    }
    {
        // Eye between light and surface, eye offset 45o
        auto eye = ngl::Vec4(0.0f,std::sqrt(2)/2,-std::sqrt(2)/2);
        auto normal = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.0f,-10.0f));
        auto result = m.lighting(light, pos, eye, normal);
        ASSERT_EQ(result, ngl::Vec3(1.0f,1.0f,1.0f));
    }
    {
        // Eye between light and surface, eye offset 45o
        auto eye = ngl::Vec4(0.0f,std::sqrt(2)/2,-std::sqrt(2)/2);
        auto normal = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.0f,-10.0f));
        auto result = m.lighting(light, pos, eye, normal);
        ASSERT_EQ(result, ngl::Vec3(1.0f,1.0f,1.0f));
    }
    {
        // Elighting with eye opposite surface, light offset 45o
        auto eye = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto normal = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,10.0f,-10.0f));
        auto result = m.lighting(light, pos, eye, normal);
        ASSERT_EQ(result, ngl::Vec3(0.7364f, 0.7364f, 0.7364f));
    }
    {
        // Eye in the path of reflaction vector
        auto eye = ngl::Vec4(0.0f,-std::sqrt(2)/2,-std::sqrt(2)/2);
        auto normal = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,10.0f,-10.0f));
        auto result = m.lighting(light, pos, eye, normal);
        ASSERT_EQ(result, ngl::Vec3(0.7364f, 0.7364f, 0.7364f));
    }
    {
        // Light behind the surface
        auto eye = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto normal = ngl::Vec4(0.0f,0.0f,-1.0f);
        auto light = Light(ngl::Vec3(1.0f,1.0f,1.0f), ngl::Vec4(0.0f,0.0f,10.0f));
        auto result = m.lighting(light, pos, eye, normal);
        ASSERT_EQ(result, ngl::Vec3(0.1f, 0.1f, 0.1f));
    }
}