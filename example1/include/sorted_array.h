#pragma once	//guardia per non far includere più volte un file

typedef struct _SortedArray SortedArray;

typedef int (*SortedArrayCmp)(void*, void*);

/**
 * crea una nuova struttura SortedArray
 */
SortedArray* SortedArray_new(SortedArrayCmp);//costruttore

/**
 * inserisce nel sortedArray inviato 
 * l'oggetto obj passato come parametro
 */
void SortedArray_free(SortedArray* sa);//distruttore

/**
 * inserisce nel sortedArray inviato 
 * l'oggetto obj passato come parametro
 */
void SortedArray_insert(SortedArray* sa, void* obj);//inserimento

/**
 * cancella dal sortedArray inviato 
 * l'elemento di posizione 'pos' qualora esista
 */
void SortedArray_remove(SortedArray* sa, int pos);//cancellazione

/**
 * restituisce l'oggetto di posizione pos
 */
void* SortedArray_get(SortedArray* sa, int pos);

/**
 * ridimensiona in SortedArray
 */
void SortedArray_resize(SortedArray* sa, size_t memsize);

/**
 * restituisce il numero di elementi presenti nell'array
 */
int SortedArray_size(SortedArray* sa);

