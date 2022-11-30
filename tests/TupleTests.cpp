#include <gtest/gtest.h>

#include "Tuple.h"

TEST(Tuple, construct)
{
    auto t = Tuple();
    ASSERT_EQ(t.getX(), 0.0f);
    ASSERT_EQ(t.getY(), 0);
}

TEST(Tuple, userCtor)
{
    auto t = Tuple(1,2);
    ASSERT_EQ(t.getX(), 1);
    ASSERT_EQ(t.getY(), 2);
}