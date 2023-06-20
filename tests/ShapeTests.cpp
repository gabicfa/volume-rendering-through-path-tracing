#include <gtest/gtest.h>
#include "Shape.h"
#include "TestShape.h"
#include "Group.h"
#include "Sphere.h"

TEST(ShapeTest, ShapeHasParentAttribute)
{
    // Create a test shape
    auto s = std::make_shared<TestShape>();

    ASSERT_EQ(s->parent(), nullptr);
}

TEST(ShapeTest, ConvertPointFromWorldToObjectSpace)
{
    auto g1 = std::make_shared<Group>();
    g1->setTransform(ngl::Mat4::rotateY(90));

    auto g2 = std::make_shared<Group>();
    g2->setTransform(ngl::Mat4::scale(2, 2, 2));

    auto s = std::make_shared<Sphere>();
    s->setTransform(ngl::Mat4::translate(5, 0, 0));

    g1->addChild(g2);
    g2->addChild(s);

    ngl::Vec4 point(-2, 0, -10);
    ngl::Vec4 convertedPoint = s->worldToObject(point);

    ASSERT_NEAR(convertedPoint[0], 0.0f, 0.001f);
    ASSERT_NEAR(convertedPoint[1], 0.0f, 0.001f);
    ASSERT_NEAR(convertedPoint[2], -1.0f, 0.001f);
}