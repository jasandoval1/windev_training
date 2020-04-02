// test.cpp
//
// Test suite implementation.

#include "gtest/gtest.h"

// include declarations for functions under test
#include <utils.hpp>

TEST(FactorialTest, FactorialCompute) 
{
    EXPECT_EQ(factorial(1), 1u);
    EXPECT_EQ(factorial(2), 2u);
    EXPECT_EQ(factorial(3), 6u);
    EXPECT_EQ(factorial(10), 3628800u);
}
