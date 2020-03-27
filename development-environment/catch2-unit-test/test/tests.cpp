// test.cpp

#include <catch2/catch.hpp>
#include <utils.hpp>

TEST_CASE("factorials are computed correctly")
{
    REQUIRE(factorial(1) == 1);
    REQUIRE(factorial(2) == 2);
    REQUIRE(factorial(3) == 6);
    REQUIRE(factorial(10) == 3628800);
}