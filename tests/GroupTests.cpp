#include <gtest/gtest.h>
#include "Ray.h"
#include "Group.h"
#include "TestShape.h"

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