#pragma once	//guardia per non far includere più volte un file

/*
*funzione utilizzata per comparare due Record(elementi)
*/
typedef int (*recordCmp)(void*, void*);

/*
* ordinamento di tipo insertionSort su un array generico
*/
void insertion_sort(void** array, int length, recordCmp cmpfunc);

/*
* ordinamento di tipo quickSort su un array generico
*/
void quicksort(void** array, int length, recordCmp cmpfunc);

void quicksortRec(void** array, int i, int f, recordCmp cmpfunc);

int partition(void** array, int c, int f, recordCmp cmpfunc);