#include <gtest/gtest.h>
#include "Ray.h"
#include "Group.h"
#include "TestShape.h"
#include "Sphere.h"

TEST(GroupTest, CreatingNewGroup)
{
    Group g;

    ngl::Mat4 identity;
    identity.identity();

    ASSERT_EQ(g.transform(), identity);
    ASSERT_TRUE(g.getChildren().empty());
}

TEST(GroupTest, AddChildToGroup)
{
    auto g = std::make_shared<Group>();
    auto s = std::make_shared<TestShape>();

    g->addChild(s);

    ASSERT_FALSE(g->getChildren().empty());
    ASSERT_TRUE(std::find(g->getChildren().begin(), g->getChildren().end(), s) != g->getChildren().end());
    ASSERT_EQ(s->parent(), g);
}

TEST(GroupTest, IntersectRayWithEmptyGroup)
{
    auto g = std::make_shared<Group>();
    Ray r(ngl::Vec4(0.0f, 0.0f, 0.0f), ngl::Vec4(0.0f, 0.0f, 1.0f));

    std::vector<Intersection> xs = g->intersect(r);

    ASSERT_TRUE(xs.empty());
}

TEST(GroupTest, IntersectRayWithNonEmptyGroup)
{
    auto g = std::make_shared<Group>();
    auto s1 = std::make_shared<Sphere>();
    auto s2 = std::make_shared<Sphere>();
    auto s3 = std::make_shared<Sphere>();

    s2->setTransform(ngl::Mat4::translate(0, 0, -3));
    s3->setTransform(ngl::Mat4::translate(5, 0, 0));

    g->addChild(s1);
    g->addChild(s2);
    g->addChild(s3);

    Ray r(ngl::Vec4(0, 0, -5), ngl::Vec4(0, 0, 1));

    std::vector<Intersection> xs = g->localIntersect(r);

    ASSERT_EQ(xs.size(), 4);
    ASSERT_TRUE(*(xs[0].object()) == *s2);
    ASSERT_TRUE(*(xs[1].object()) == *s2);
    ASSERT_TRUE(*(xs[2].object()) == *s1);
    ASSERT_TRUE(*(xs[3].object()) == *s1);
}

TEST(GroupTest, IntersectingTransformedGroup)
{
    auto g = std::make_shared<Group>();
    g->setTransform(ngl::Mat4::scale(2, 2, 2));

    Sphere s;
    s.setTransform(ngl::Mat4::translate(5, 0, 0));

    g->addChild(std::make_shared<Sphere>(s));

    Ray r(ngl::Vec4(10, 0, -10), ngl::Vec4(0, 0, 1));

    std::vector<Intersection> xs = g->intersect(r);

    ASSERT_EQ(xs.size(), 2);
}