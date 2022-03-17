#include <stdlib.h>
#include "unity.h"
#include "sorted_array.h"

int* int_new(int n){
	int* res= (int*)malloc(sizeof(int));
	*res=n;

	return res;
}

static int compare_ints(int* a, int* b){
	return (*a - *b);
}

static SortedArray* create_test_object(){
	SortedArray* sa= SortedArray_new((SortedArrayCmp)compare_ints);
	SortedArray_insert(sa, int_new(3));
	SortedArray_insert(sa, int_new(4));
	SortedArray_insert(sa, int_new(7));
	SortedArray_insert(sa, int_new(11));

	return sa;
}

static void delete_test_object(SortedArray* sa){
	for (int i = 0; i < SortedArray_size(sa); ++i){
		free(SortedArray_get(sa,i));
	}

	SortedArray_free(sa);
}

void sorted_array_create_zero_sized_array(){
	SortedArray* sa= SortedArray_new((SortedArrayCmp)compare_ints);
	TEST_ASSERT_EQUAL(0, SortedArray_size(sa));

	SortedArray_free(sa);
}

void sorted_array_insert_middle(){
	SortedArray* sa= create_test_object();

	SortedArray_insert(sa, int_new(6));

	TEST_ASSERT_EQUAL(3, *(int*) SortedArray_get(sa,0));
	TEST_ASSERT_EQUAL(4, *(int*) SortedArray_get(sa,1));
	TEST_ASSERT_EQUAL(6, *(int*) SortedArray_get(sa,2));
	TEST_ASSERT_EQUAL(7, *(int*) SortedArray_get(sa,3));
	TEST_ASSERT_EQUAL(11,*(int*) SortedArray_get(sa,4));

	delete_test_object(sa);
}

void sorted_array_insert_tail(){
	SortedArray* sa= create_test_object();

	SortedArray_insert(sa, int_new(15));

	TEST_ASSERT_EQUAL(3, *(int*) SortedArray_get(sa,0));
	TEST_ASSERT_EQUAL(4, *(int*) SortedArray_get(sa,1));
	TEST_ASSERT_EQUAL(7, *(int*) SortedArray_get(sa,2));
	TEST_ASSERT_EQUAL(11,*(int*)  SortedArray_get(sa,3));
	TEST_ASSERT_EQUAL(15,*(int*)  SortedArray_get(sa,4));

	delete_test_object(sa);
}

void sorted_array_insert_head(){
	SortedArray* sa= create_test_object();

	SortedArray_insert(sa, int_new(1));

	TEST_ASSERT_EQUAL(1, *(int*) SortedArray_get(sa,0));
	TEST_ASSERT_EQUAL(3, *(int*) SortedArray_get(sa,1));
	TEST_ASSERT_EQUAL(4, *(int*) SortedArray_get(sa,2));
	TEST_ASSERT_EQUAL(7, *(int*) SortedArray_get(sa,3));
	TEST_ASSERT_EQUAL(11,*(int*)  SortedArray_get(sa,4));

	delete_test_object(sa);
}

void sorted_array_remove(){
	SortedArray* sa= create_test_object();

	free(SortedArray_get(sa,2));
	SortedArray_remove(sa, 2);

	TEST_ASSERT_EQUAL(3, *(int*) SortedArray_get(sa,0));
	TEST_ASSERT_EQUAL(4, *(int*) SortedArray_get(sa,1));
	TEST_ASSERT_EQUAL(11,*(int*)  SortedArray_get(sa,2));
	TEST_ASSERT_EQUAL(3, SortedArray_size(sa));

	delete_test_object(sa);
}
int main(){
	UNITY_BEGIN();

	RUN_TEST(sorted_array_create_zero_sized_array);
	RUN_TEST(sorted_array_insert_middle);
	RUN_TEST(sorted_array_insert_tail);
	RUN_TEST(sorted_array_insert_head);
	RUN_TEST(sorted_array_remove);
	UNITY_END();
}