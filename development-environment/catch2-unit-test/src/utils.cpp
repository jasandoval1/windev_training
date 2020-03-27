// utils.cpp
//
// Utility functions.

#include "utils.hpp"

unsigned int factorial(unsigned int n)
{
    // suspicious factorial implementation...
    return n < 1 ? n : factorial(n - 1) * n;
}