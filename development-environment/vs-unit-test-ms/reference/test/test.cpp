// test.cpp
//
// Test suite implementation.

#include "CppUnitTest.h"

#include <list.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

typedef struct point
{
	int x;
	int y;
} point_t;

void custom_print_noop(void*) {}
void custom_delete_noop(void*) {}

void custom_print_point(void* ptr)
{
	point_t* p = (point_t*)ptr;
	printf("(%d, %d)", p->x, p->y);
}

void custom_delete_point(void* ptr)
{
	point_t* p = (point_t*)ptr;
	free(p);
}

namespace test
{
	TEST_CLASS(ListTest)
	{
	public:
		
		TEST_METHOD(Construction)
		{
			list_t* l = list_create(custom_print_noop, custom_delete_noop);
			Assert::IsNotNull(l);

			list_destroy(l);
		}

		TEST_METHOD(Insert)
		{
			list_t* l = list_create(custom_print_point, custom_delete_point);
			Assert::IsNotNull(l);

			point_t* p1 = (point_t*)calloc(1, sizeof(point_t));
			Assert::IsNotNull(p1);
			p1->x = 1;
			p1->y = 2;

			// successful initial insert
			Assert::AreEqual(list_insert(l, 1, p1), 0);
			Assert::AreEqual(list_size(l), 1);

			point_t* p2 = (point_t*)calloc(1, sizeof(point_t));
			Assert::IsNotNull(p2);
			p2->x = 1;
			p2->y = 2;

			// successful non-initial insert
			Assert::AreEqual(list_insert(l, 2, p2), 0);
			Assert::AreEqual(list_size(l), 2);

			point_t* p3 = (point_t*)calloc(1, sizeof(point_t));
			Assert::IsNotNull(p3);
			p3->x = 1;
			p3->y = 2;

			// failed non-initial insert, size unchanged
			Assert::AreEqual(list_insert(l, 2, p3), 1);
			Assert::AreEqual(list_size(l), 2);
			free(p3);

			list_destroy(l);
		}

		TEST_METHOD(Find)
		{
			list_t* l = list_create(custom_print_point, custom_delete_point);
			Assert::IsNotNull(l);

			point_t* p = (point_t*)calloc(1, sizeof(point_t));
			Assert::IsNotNull(p);
			p->x = 1;
			p->y = 2;

			Assert::AreEqual(list_insert(l, 1, p), 0);
			Assert::AreEqual(list_size(l), 1);

			// search for an existing key
			point_t* r1 = (point_t*)list_find(l, 1);
			Assert::IsNotNull(r1);
			Assert::AreEqual(r1->x, 1);
			Assert::AreEqual(r1->y, 2);

			// search for a non-existent key
			point_t* r2 = (point_t*)list_find(l, 2);
			Assert::IsNull(r2);

			list_destroy(l);
		}

		TEST_METHOD(Remove)
		{
			list_t* l = list_create(custom_print_point, custom_delete_point);
			Assert::IsNotNull(l);

			point_t* p = (point_t*)calloc(1, sizeof(point_t));
			Assert::IsNotNull(p);
			p->x = 1;
			p->y = 2;

			Assert::AreEqual(list_insert(l, 1, p), 0);
			Assert::AreEqual(list_size(l), 1);

			// attempt to remove non-existent key
			point_t* r1 = (point_t*)list_remove(l, 2);
			Assert::IsNull(r1);
			Assert::AreEqual(list_size(l), 1);

			// attempt to remove existing key
			point_t* r2 = (point_t*)list_remove(l, 1);
			Assert::IsNotNull(r2);
			Assert::AreEqual(list_size(l), 0);
			free(r2);

			list_destroy(l);
		}
	};
}
