#include <stdlib.h>
#include "unity.h"
#include "sorting_G.h"

int* int_new(int n){
	int* res= (int*)malloc(sizeof(int));
	*res=n;

	return res;
}

static int compare_ints(int* a, int* b){
	return (*a - *b);
}

void print_array(int** j,int n){
	for (int i = 0; i < n; ++i){
		printf("%d\n", *j[i]);
	}
}

void test_free(int** j, int n){
	for (int i = 0; i < n; ++i){
		free(j[i]);
	}
	free(j);
}

void insertion_test(){
	
	int dim =5;
	int** j = (int**)malloc(sizeof(int*)*5);
	j[0]=int_new(7);
	j[1]=int_new(3);
	j[2]=int_new(9);
	j[3]=int_new(1);
	j[4]=int_new(2);

	insertion_sort((void**) j, dim, (recordCmp)compare_ints);

	TEST_ASSERT_EQUAL(1,*j[0]);
	TEST_ASSERT_EQUAL(2,*j[1]);
	TEST_ASSERT_EQUAL(3,*j[2]);
	TEST_ASSERT_EQUAL(7,*j[3]);
	TEST_ASSERT_EQUAL(9,*j[4]);

	test_free(j, dim);
}

void insertion_test_void(){
	int** j= NULL;
	int dim=0;
	insertion_sort((void**) j, dim, (recordCmp)compare_ints);
	test_free(j, dim);
}

void insertion_test_preorder(){
	int dim=5;
	int** j = (int**)malloc(sizeof(int*)*dim);
	j[0]=int_new(1);
	j[1]=int_new(2);
	j[2]=int_new(3);
	j[3]=int_new(4);
	j[4]=int_new(5);

	insertion_sort((void**) j, dim, (recordCmp)compare_ints);

	TEST_ASSERT_EQUAL(1,*j[0]);
	TEST_ASSERT_EQUAL(2,*j[1]);
	TEST_ASSERT_EQUAL(3,*j[2]);
	TEST_ASSERT_EQUAL(4,*j[3]);
	TEST_ASSERT_EQUAL(5,*j[4]);

	test_free(j, dim);
}

void quicksort_test(){
	int dim =5;
	int** j = (int**)malloc(sizeof(int*)*dim);
	j[0]=int_new(4);
	j[1]=int_new(3);
	j[2]=int_new(2);
	j[3]=int_new(1);
	j[4]=int_new(0);

	quicksort((void**) j, dim, (recordCmp)compare_ints);

	TEST_ASSERT_EQUAL(0,*j[0]);
	TEST_ASSERT_EQUAL(1,*j[1]);
	TEST_ASSERT_EQUAL(2,*j[2]);
	TEST_ASSERT_EQUAL(3,*j[3]);
	TEST_ASSERT_EQUAL(4,*j[4]);

	test_free(j, dim);
}

void quicksort_test_preorder(){
	int dim =5;
	int** j = (int**)malloc(sizeof(int*)*dim);
	j[0]=int_new(1);
	j[1]=int_new(2);
	j[2]=int_new(3);
	j[3]=int_new(4);
	j[4]=int_new(5);

	quicksort((void**) j, dim, (recordCmp)compare_ints);

	TEST_ASSERT_EQUAL(1,*j[0]);
	TEST_ASSERT_EQUAL(2,*j[1]);
	TEST_ASSERT_EQUAL(3,*j[2]);
	TEST_ASSERT_EQUAL(4,*j[3]);
	TEST_ASSERT_EQUAL(5,*j[4]);

	test_free(j, dim);
}

void quicksort_test_void(){
	int dim =0;
	int** j = (int**)malloc(sizeof(int*)*dim);

	quicksort((void**) j, dim, (recordCmp)compare_ints);

	test_free(j, dim);
}
int main(){
	UNITY_BEGIN();

	RUN_TEST(insertion_test);
	RUN_TEST(insertion_test_void);
	RUN_TEST(insertion_test_preorder);

	RUN_TEST(quicksort_test);
	RUN_TEST(quicksort_test_void);
	RUN_TEST(quicksort_test_preorder);

	UNITY_END();
}