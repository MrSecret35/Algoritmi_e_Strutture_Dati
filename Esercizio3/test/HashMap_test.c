#include <stdlib.h>
#include <string.h>
#include "unity.h"
#include "hashMap.h"


int* int_new(int n){
	int* res= (int*)malloc(sizeof(int));
	*res=n;

	return res;
}
int hf(int* a){
	return *a%10;
}
int cmpf(int* a, int* b){
	return *a-*b;
}


int hf_char(char* a){
	int x=0;
	for(int i=0; i<2;i++ ){
		x= x + (int)(*(a+i));
	}
	return x%10;
}
int cmpf_char(char* a, char* b){
	return strcmp(a, b);
}

void control_Key_char(){
	char s1[]={'a','b'};
	char s2[]={'c','d'};
	char s3[]={'e','f'};
	char s4[]={'a','z'};

	HashMap* g= HashMap_create((hash_function) hf_char, (cmp_function) cmpf_char);
	
	g=HashMap_insert(g,(void*)s1,(void*)int_new(1));
	g=HashMap_insert(g,(void*)s2,(void*)int_new(3));
	g=HashMap_insert(g,(void*)s2,(void*)int_new(4));
	TEST_ASSERT_EQUAL(1,HashMap_isKey(g,(void*)s1));
	TEST_ASSERT_EQUAL(0,HashMap_isKey(g,(void*)s4));

	TEST_ASSERT_EQUAL(2,HashMap_n_associazioni(g));
	
	HashMap_delete(g);

}

void empty(){
	//TEST_ASSERT_EQUAL(5,*j[4]);
	HashMap* g= HashMap_create((hash_function) hf, (cmp_function) cmpf);
	TEST_ASSERT_EQUAL(1,HashMap_isEmpty(g));
	TEST_ASSERT_EQUAL(0,HashMap_n_associazioni(g));
	HashMap_delete(g);
}

void insert(){
	//TEST_ASSERT_EQUAL(5,*j[4]);

	HashMap* g= HashMap_create((hash_function) hf, (cmp_function) cmpf);
	g=HashMap_insert(g,(void*)int_new(14),(void*)int_new(1));
	g=HashMap_insert(g,(void*)int_new(14),(void*)int_new(2));
	g=HashMap_insert(g,(void*)int_new(154),(void*)int_new(3));
	g=HashMap_insert(g,(void*)int_new(19),(void*)int_new(4));
	TEST_ASSERT_EQUAL(3,HashMap_n_associazioni(g));
	TEST_ASSERT_EQUAL(0,HashMap_isEmpty(g));

	HashMap_delete(g);
}

void delete_association(){
	HashMap* g= HashMap_create((hash_function) hf, (cmp_function) cmpf);
	g=HashMap_insert(g,(void*)int_new(14),(void*)int_new(1));
	g=HashMap_insert(g,(void*)int_new(14),(void*)int_new(2));
	g=HashMap_insert(g,(void*)int_new(154),(void*)int_new(3));
	g=HashMap_insert(g,(void*)int_new(19),(void*)int_new(4));
	g=HashMap_delete_all_association(g);
	TEST_ASSERT_EQUAL(0,HashMap_n_associazioni(g));
	TEST_ASSERT_EQUAL(1,HashMap_isEmpty(g));

	HashMap_delete(g);
}

void control_Key(){
	HashMap* g= HashMap_create((hash_function) hf, (cmp_function) cmpf);
	g=HashMap_insert(g,(void*)int_new(14),(void*)int_new(1));
	g=HashMap_insert(g,(void*)int_new(154),(void*)int_new(3));
	g=HashMap_insert(g,(void*)int_new(19),(void*)int_new(4));

	TEST_ASSERT_EQUAL(1,HashMap_isKey(g,int_new(14)));
	TEST_ASSERT_EQUAL(0,HashMap_isKey(g,int_new(15)));
	TEST_ASSERT_EQUAL(3,HashMap_n_associazioni(g));
	TEST_ASSERT_EQUAL(1,*(int*)HashMap_getValue(g,int_new(14)));
	TEST_ASSERT_EQUAL(3,*(int*)HashMap_getValue(g,int_new(154)));

	TEST_ASSERT_EQUAL(-1,*(int*)HashMap_getValue(g,int_new(159)));
	
	g=HashMap_delete_association(g,int_new(14));

	TEST_ASSERT_EQUAL(0,HashMap_isKey(g,int_new(14)));

	TEST_ASSERT_EQUAL(-1,*(int*)HashMap_getValue(g,int_new(14)));

	TEST_ASSERT_EQUAL(2,HashMap_n_associazioni(g));
	HashMap_delete(g);

}

void get_key(){
	HashMap* g= HashMap_create((hash_function) hf, (cmp_function) cmpf);
	g=HashMap_insert(g,(void*)int_new(14),(void*)int_new(1));
	g=HashMap_insert(g,(void*)int_new(154),(void*)int_new(2));
	g=HashMap_insert(g,(void*)int_new(18),(void*)int_new(3));
	g=HashMap_insert(g,(void*)int_new(28),(void*)int_new(3));

	TEST_ASSERT_EQUAL(3,*(int*)HashMap_getValue(g,int_new(28)));
	TEST_ASSERT_EQUAL(3,*(int*)HashMap_getValue(g,int_new(18)));

	TEST_ASSERT_EQUAL(4,HashMap_n_associazioni(g));

	void** a=HashMap_getAllKey(g); 
	TEST_ASSERT_EQUAL(14, *(int*)a[0]);
	TEST_ASSERT_EQUAL(154,*(int*)a[1]);
	TEST_ASSERT_EQUAL(18,*(int*)a[2]);
	
	HashMap_delete(g);
}


int main(){
	UNITY_BEGIN();

	RUN_TEST(empty);

	RUN_TEST(insert);

	RUN_TEST(delete_association);

	RUN_TEST(control_Key);

	RUN_TEST(control_Key_char);

	RUN_TEST(control_Key_char);

	RUN_TEST(get_key);

	UNITY_END();
}