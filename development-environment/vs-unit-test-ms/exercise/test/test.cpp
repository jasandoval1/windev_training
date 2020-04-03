// test.cpp
//
// Unit test implementation.

#include "CppUnitTest.h"

// pull in the declaration for functions under test
#include <utils.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace test
{
	TEST_CLASS(FactorialTest)
	{
	public:
		
		TEST_METHOD(FactorialCompute1)
		{
			Assert::AreEqual(factorial(1), 1u);
			Assert::AreEqual(factorial(2), 2u);
			Assert::AreEqual(factorial(3), 6u);
			Assert::AreEqual(factorial(10), 3628800u);
		}
	};
}
