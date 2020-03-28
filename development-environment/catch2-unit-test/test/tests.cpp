// test.cpp

#include <catch2/catch.hpp>
#include <utils.hpp>

TEST_CASE("factorials are computed correctly")
{
    REQUIRE(factorial(1) == 1u);
    REQUIRE(factorial(2) == 2u);
    REQUIRE(factorial(3) == 6u);
    REQUIRE(factorial(10) == 3628800u);
}