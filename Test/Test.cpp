#include "gtest/gtest.h"

#include "MathUtility.h"

// Tests factorial for zero
TEST(FactorialTest, HandlesZeroInput)
{
	EXPECT_EQ(1, factorial(0));
}

// Tests factorial of positive numbers
TEST(FactorialTest, HandlesPositiveInput)
{
	EXPECT_EQ(1, factorial(1));
	EXPECT_EQ(2, factorial(2));
	EXPECT_EQ(6, factorial(3));
	EXPECT_EQ(40320, factorial(8)) << "Factorial (8) Error";
}

// Tests for nCr
TEST(MathsUtility_Test, nCr)
{
    
}

// Tests for nPr
TEST(MathsUtility_Test, nPr)
{

}

// Tests for nTermAP
TEST(MathsUtility_Test, nTermAP)
{
    EXPECT_EQ(20, nTermAP(0, 5, 5));
    EXPECT_EQ(19, nTermAP(3, 2, 9));
    EXPECT_EQ(13, nTermAP(1, 4, 4));
}

// Tests for summationAP
TEST(MathsUtility_Test, summationAP)
{
    EXPECT_EQ(50, summationAP(0, 5, 5));
    EXPECT_EQ(99, summationAP(3, 2, 9));
    EXPECT_EQ(28, summationAP(1, 4, 4));
}