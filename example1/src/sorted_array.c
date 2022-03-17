#include<stdlib.h>

#include "sorted_array.h"
#define INIT_CAPACITY 100
struct _SortedArray{
	void** array;
	SortedArrayCmp compare;
	int capacity;
	int size;
};

SortedArray* SortedArray_new(SortedArrayCmp compare){
	SortedArray* res = (SortedArray*)malloc(sizeof(SortedArray));
	res->capacity=INIT_CAPACITY;
	res->array=(void**) malloc(sizeof(void*) * res->capacity);
	res->size=0;

	res->compare=compare;

	return res;
}

void SortedArray_free(SortedArray* sa){
	free(sa->array);
	free(sa);
}

void SortedArray_insert(SortedArray* sa, void* obj){
	//for(int i=0; i<size && sa->compare(*(sa->array+i), obj)>0 ; i++){}
	if(sa->capacity==sa->size){
		SortedArray_resize(sa,sa->capacity*2);
	}
	int i;
	for(i=sa->size-1; i>=0 && sa->compare(sa->array[i], obj)>0 ; i--){
		sa->array[i+1]= sa->array[i];
	}
	sa->array[i+1]=obj;
	sa->size=sa->size+1;
}

void SortedArray_remove(SortedArray* sa, int pos){
	for(int i=pos; i<sa->size-1; i++){
		sa->array[pos]= sa->array[pos+1];
	}
	sa->size--;

	if(sa->capacity>sa->size*2){
		SortedArray_resize(sa,sa->capacity/2);
	}
}

void* SortedArray_get(SortedArray* sa, int pos){
	return sa->array[pos];
}

void SortedArray_resize(SortedArray* sa, size_t memsize){
	sa->capacity= memsize;
	sa->array= (void**)realloc(sa->array, sa->capacity);
}

int SortedArray_size(SortedArray* sa){
	return sa->size;
}