#include <gtest/gtest.h>
#include "../src/z10/Vector2D.h"

TEST(Rotate_correct, rotate_to_90)
{
    Vector2D vector(1, 1);
    rotate(vector, 90);
    Vector2D targetVector(1, -1);
    EXPECT_EQ(true, vector == targetVector);
}

TEST(Rotate_correct, rotate_to_180)
{
    Vector2D vector(1, 1);
    rotate(vector, 180);
    Vector2D targetVector(-1, -1);
    EXPECT_EQ(true, vector == targetVector);
}

TEST(Rotate_correct, rotate_to_270)
{
    Vector2D vector(1, 1);
    rotate(vector, 270);
    Vector2D targetVector(-1, 1);
    EXPECT_EQ(true, vector == targetVector);
}

TEST(Rotate_incorrect, rotate_to_13)
{
    Vector2D vector(1, 1);
    EXPECT_EQ(false, rotate(vector, 13));
}