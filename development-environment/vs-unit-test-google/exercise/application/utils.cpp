// utils.cpp
//
// Utility functions.

#include "utils.hpp"

unsigned int factorial(unsigned int n)
{
	return n < 1 ? n : factorial(n - 1) * n;
}