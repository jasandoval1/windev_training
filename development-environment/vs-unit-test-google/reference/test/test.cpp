// test.cpp
//
// Test suite implementation.

#include "gtest/gtest.h"

#include <thread>
#include <stdio.h>
#include <string.h>

#include <list.hpp>

typedef struct point
{
	int x;
	int y;
} point_t;

void custom_print_noop(void*)  {}
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

TEST(ListTest, Construction) 
{
	list_t* l = list_create(custom_print_noop, custom_delete_noop);
	ASSERT_NE(l, nullptr);

	list_destroy(l);
}

TEST(ListTest, Insert)
{
	list_t* l = list_create(custom_print_point, custom_delete_point);
	ASSERT_NE(l, nullptr);

	point_t* p1 = (point_t*)calloc(1, sizeof(point_t));
	ASSERT_NE(p1, nullptr);
	p1->x = 1;
	p1->y = 2;

	// successful initial insert
	EXPECT_EQ(list_insert(l, 1, p1), 0);
	EXPECT_EQ(list_size(l), 1);

	point_t* p2 = (point_t*)calloc(1, sizeof(point_t));
	ASSERT_NE(p2, nullptr);
	p2->x = 1;
	p2->y = 2;

	// successful non-initial insert
	EXPECT_EQ(list_insert(l, 2, p2), 0);
	EXPECT_EQ(list_size(l), 2);

	point_t* p3 = (point_t*)calloc(1, sizeof(point_t));
	ASSERT_NE(p3, nullptr);
	p3->x = 1;
	p3->y = 2;

	// failed non-initial insert, size unchanged
	ASSERT_EQ(list_insert(l, 2, p3), 1);
	EXPECT_EQ(list_size(l), 2);
	free(p3);

	list_destroy(l);
}

TEST(ListTest, Find)
{
	list_t* l = list_create(custom_print_point, custom_delete_point);
	ASSERT_NE(l, nullptr);

	point_t* p = (point_t*) calloc(1, sizeof(point_t));
	ASSERT_NE(p, nullptr);
	p->x = 1;
	p->y = 2;

	ASSERT_EQ(list_insert(l, 1, p), 0);
	EXPECT_EQ(list_size(l), 1);
	
	// search for an existing key
	point_t* r1 = (point_t*) list_find(l, 1);
	ASSERT_NE(r1, nullptr);
	EXPECT_EQ(r1->x, 1);
	EXPECT_EQ(r1->y, 2);
		
	// search for a non-existent key
	point_t* r2 = (point_t*) list_find(l, 2);
	EXPECT_EQ(r2, nullptr);

	list_destroy(l);
}

TEST(ListTest, Remove)
{
	list_t* l = list_create(custom_print_point, custom_delete_point);
	ASSERT_NE(l, nullptr);

	point_t* p = (point_t*)calloc(1, sizeof(point_t));
	ASSERT_NE(p, nullptr);
	p->x = 1;
	p->y = 2;

	ASSERT_EQ(list_insert(l, 1, p), 0);
	EXPECT_EQ(list_size(l), 1);

	// attempt to remove non-existent key
	point_t* r1 = (point_t*) list_remove(l, 2);
	EXPECT_EQ(r1, nullptr);
	EXPECT_EQ(list_size(l), 1);

	// attempt to remove existing key
	point_t* r2 = (point_t*) list_remove(l, 1);
	EXPECT_NE(r2, nullptr);
	EXPECT_EQ(list_size(l), 0);
	free(r2);

	list_destroy(l);
}

TEST(ListTest, InsertMultithreaded)
{

}

TEST(ListTest, FindMultithreaded)
{

}

TEST(ListTest, RemoveMultithreaded)
{

}