#include <gtest/gtest.h>
#include "Shape.h"
#include "TestShape.h"

TEST(ShapeTest, ShapeHasParentAttribute)
{
    // Create a test shape
    auto s = std::make_shared<TestShape>();

    ASSERT_EQ(s->parent(), nullptr);
}