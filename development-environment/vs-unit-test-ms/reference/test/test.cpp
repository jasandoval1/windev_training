// test.cpp
//
// Test suite implementation.

#include "CppUnitTest.h"

#include <thread>
#include <vector>
#include <future>

#include <list.hpp>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

constexpr auto MULTITHREADED_TEST_N_THREADS          = 5;
constexpr auto MULTITHREADED_TEST_INSERTS_PER_THREAD = 10;
constexpr auto MULTITHREADED_TEST_FIND_TOTAL_INSERT  = 10;
constexpr auto MULTITHEADED_TEST_REMOVE_TOTAL_INSERT = 100;

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

void insert_async(list_t* list, int base_value)
{
	for (auto i = 0; i < MULTITHREADED_TEST_INSERTS_PER_THREAD; ++i)
	{
		point_t* p = (point_t*)calloc(1, sizeof(point_t));
		p->x = base_value + i;
		p->y = base_value + i;

		list_insert(list, base_value + i, p);
	}
}

void* find_async(list_t* list, uint32_t key)
{
	return list_find(list, key);
}

void remove_async(list_t* list, uint32_t base_key)
{
	auto max_key = base_key +
		(MULTITHEADED_TEST_REMOVE_TOTAL_INSERT / MULTITHREADED_TEST_N_THREADS);

	for (auto key = base_key; key < max_key; ++key)
	{
		point_t* p = (point_t*)list_remove(list, key);
		free(p);
	}
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

		TEST_METHOD(InsertMultithreaded)
		{
			list_t* l = list_create(custom_print_point, custom_delete_point);
			Assert::IsNotNull(l);

			// create some threads, each of which will perform some number of insertions
			auto threads = std::vector<std::thread>{};
			for (auto base = 0; base < MULTITHREADED_TEST_N_THREADS; ++base)
			{
				threads.emplace_back(insert_async, l, MULTITHREADED_TEST_INSERTS_PER_THREAD * base);
			}

			// wait for the threads to finish
			for (auto& t : threads)
			{
				t.join();
			}

			// verify that the list contains all of the expected elements
			Assert::AreEqual(list_size(l), MULTITHREADED_TEST_N_THREADS * MULTITHREADED_TEST_INSERTS_PER_THREAD);

			list_destroy(l);
		}

		TEST_METHOD(FindMultithreaded)
		{
			list_t* l = list_create(custom_print_point, custom_delete_point);
			Assert::IsNotNull(l);

			// insert 10 points
			for (auto i = 0; i < MULTITHREADED_TEST_FIND_TOTAL_INSERT; ++i)
			{
				point_t* p = (point_t*)calloc(1, sizeof(point_t));
				p->x = i;
				p->y = i;

				Assert::AreEqual(list_insert(l, i, p), 0);
			}

			Assert::AreEqual(list_size(l), MULTITHREADED_TEST_FIND_TOTAL_INSERT);

			// launch 10 async tasks to search the list for existing keys
			auto futures = std::vector<std::future<void*>>{};
			for (auto i = 0; i < 10; ++i)
			{
				futures.emplace_back(std::async(std::launch::async, find_async, l, i));
			}

			// ensure that all of the find operations succeeded
			for (auto& f : futures)
			{
				Assert::IsNotNull(f.get());
			}

			list_destroy(l);
		}

		TEST_METHOD(RemoveMultithreaded)
		{
			list_t* l = list_create(custom_print_point, custom_delete_point);
			Assert::IsNotNull(l);

			// insert 100 points
			for (auto i = 0; i < MULTITHEADED_TEST_REMOVE_TOTAL_INSERT; ++i)
			{
				point_t* p = (point_t*)calloc(1, sizeof(point_t));
				p->x = i;
				p->y = i;

				Assert::AreEqual(list_insert(l, i, p), 0);
			}

			Assert::AreEqual(list_size(l), MULTITHEADED_TEST_REMOVE_TOTAL_INSERT);

			// create some threads to remove elements concurrently
			auto threads = std::vector<std::thread>{};
			for (auto i = 0; i < MULTITHREADED_TEST_N_THREADS; ++i)
			{
				auto base_key = (MULTITHEADED_TEST_REMOVE_TOTAL_INSERT / MULTITHREADED_TEST_N_THREADS) * i;
				threads.emplace_back(remove_async, l, base_key);
			}

			// wait for them to finish
			for (auto& t : threads)
			{
				t.join();
			}

			// ensure that all elements have been successfully removed
			Assert::AreEqual(list_size(l), 0);

			list_destroy(l);
		}
	};
}
