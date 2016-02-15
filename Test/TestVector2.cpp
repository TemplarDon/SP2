#include "gtest/gtest.h"

#include "Vector2.h"
#include "MyMath.h"

TEST(Vector2Test, Contructor)
{
    Vector2 v1;
    EXPECT_NEAR(0, v1.x, Math::EPSILON);
    EXPECT_NEAR(0, v1.y, Math::EPSILON);

    Vector2 v2(5, 8);
    EXPECT_NEAR(5, v2.x, Math::EPSILON);
    EXPECT_NEAR(8, v2.y, Math::EPSILON);

    Vector2 v3(324, 324);
    EXPECT_NEAR(324, v3.x, Math::EPSILON);
    EXPECT_NEAR(324, v3.y, Math::EPSILON);
}

TEST(Vector2Test, Copy_Contructor)
{
    Vector2 v1(2323, 6746);
    Vector2 v2(v1);

    EXPECT_NEAR(2323, v2.x, Math::EPSILON);
    EXPECT_NEAR(6746, v2.y, Math::EPSILON);
}

TEST(Vector2Test, Addition)
{
    Vector2 v1 = Vector2(4, 9) + Vector2(6, 15);

    EXPECT_NEAR(10, v1.x, Math::EPSILON);
    EXPECT_NEAR(24, v1.y, Math::EPSILON);
}

TEST(Vector2Test, Subtraction)
{
    Vector2 v1 = Vector2(4, 9) - Vector2(6, 3);

    EXPECT_NEAR(-2, v1.x, Math::EPSILON);
    EXPECT_NEAR(6, v1.y, Math::EPSILON);
}

TEST(Vector2Test, Unary_Negation)
{
    Vector2 v1 = -Vector2(4, 9);

    EXPECT_NEAR(-4, v1.x, Math::EPSILON);
    EXPECT_NEAR(-9, v1.y, Math::EPSILON);
}

TEST(Vector2Test, Scalar_Multiplication)
{
    Vector2 v1 = Vector2(4, 9) * 2;

    EXPECT_NEAR(8, v1.x, Math::EPSILON);
    EXPECT_NEAR(18, v1.y, Math::EPSILON);
}

TEST(Vector2Test, Magnitude)
{
    Vector2 v1 = Vector2(3, 4);

    EXPECT_NEAR(5, v1.Length(), Math::EPSILON);
}

TEST(Vector2Test, Dot_Product)
{
    Vector2 v1(3, 4);
    Vector2 v2(5, 8);

    EXPECT_NEAR(15 + 32, v1.Dot(v2), Math::EPSILON);
}

TEST(Vector2Test, Normalized)
{
    Vector2 v1(3, 4);
    v1.Normalized();

    EXPECT_NEAR(0.6f, v1.x, Math::EPSILON);
    EXPECT_NEAR(0.8f, v1.y, Math::EPSILON);
}