#include<stdlib.h>
#include "sorting_G.h"

void insertion_sort(void** array, int length, recordCmp cmpfunc){
	for(int i=1; i<length; i++){
		void* key=array[i];
		int j=i-1;
		while(j>=0 && cmpfunc(array[j],key)>0){
			array[j+1]=array[j];
			j--;
		}
		array[j+1]=key;
	} 
}

void quicksort(void** array, int length, recordCmp cmpfunc){
	if(length>0){
		quicksortRec(array, 0, length-1, cmpfunc);
	}
}

void quicksortRec(void** array, int i, int f, recordCmp cmpfunc){
	if(f>1){
		int p=partition(array, i, f, cmpfunc);
		if(p>i+1){
			quicksortRec(array, i, p-1, cmpfunc);
		}
		if(p<f-1){
			quicksortRec(array, p+1, f, cmpfunc);
		}
	}
}

int partition(void** array, int p, int q, recordCmp cmpfunc){
	int i=p;
	int j=q;


	while(i<=j){
		while(cmpfunc(array[j], array[p])>0){ j--; }
		while(i<=j && cmpfunc(array[i], array[p])<=0){ i++; }
		if(i<j){
			//scambia a[i] con a[j]
			void* t=array[i];
			array[i]=array[j];
			array[j]=t;

			i=i+1;
			j=j-1;
		}
	}

	//scambia a[p] con a[j]
	void* t=array[p];
	array[p]=array[j];
	array[j]=t;

	return j;
}