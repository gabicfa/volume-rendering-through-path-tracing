#include <gtest/gtest.h>
#include "Shape.h"
#include "TestShape.h"
#include "Group.h"
#include "Sphere.h"

TEST(ShapeTest, ShapeHasParentAttribute)
{
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

TEST(ShapeTest, ConvertNormalFromObjectToWorldSpace)
{
    auto g1 = std::make_shared<Group>();
    g1->setTransform(ngl::Mat4::rotateY(90));

    auto g2 = std::make_shared<Group>();
    g2->setTransform(ngl::Mat4::scale(1, 2, 3));

    auto s = std::make_shared<Sphere>();
    s->setTransform(ngl::Mat4::translate(5, 0, 0));

    g1->addChild(g2);
    g2->addChild(s);

    ngl::Vec4 normal(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3, 0.0f);
    ngl::Vec4 convertedNormal = s->normalToWorld(normal);

    ASSERT_NEAR(convertedNormal[0], 0.2857f, 0.001f);
    ASSERT_NEAR(convertedNormal[1], 0.4286f, 0.001f);
    ASSERT_NEAR(convertedNormal[2], -0.8571f, 0.001f);
}

TEST(ShapeTest, FindNormalOnChildObject)
{
    auto g1 = std::make_shared<Group>();
    g1->setTransform(ngl::Mat4::rotateY(90));

    auto g2 = std::make_shared<Group>();
    g2->setTransform(ngl::Mat4::scale(1, 2, 3));
    g1->addChild(g2);

    auto s = std::make_shared<Sphere>();
    s->setTransform(ngl::Mat4::translate(5, 0, 0));
    g2->addChild(s);

    ngl::Vec4 worldPoint(1.7321, 1.1547, -5.5774);
    ngl::Vec4 normal = s->normalAt(worldPoint);

    ngl::Vec4 expectedNormal(0.2857, 0.4286, -0.8571);

    ASSERT_NEAR(normal[0], expectedNormal[0], 0.001f);
    ASSERT_NEAR(normal[1], expectedNormal[1], 0.001f);
    ASSERT_NEAR(normal[2], expectedNormal[2], 0.001f);
}