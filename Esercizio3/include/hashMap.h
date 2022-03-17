#pragma once	//guardia per non far includere più volte un file

#define SIZE 20

typedef struct _Record Record;

typedef struct _HashMap HashMap;

typedef int (*hash_function)(void*);
typedef int (*cmp_function)(void*, void*);

/*
*costruttore di una hash map
*/
HashMap* HashMap_create(hash_function Fun, cmp_function cmp);

/*
*dealloca l'intera mappa
*/
void HashMap_delete(HashMap* d);

/*
*metodo interno per deallocare una lista
*/
void dealloc_list(Record* rec);

/*
*restituisce la mappa eliminando tutte le associazioni(mappa vuota)
*/
HashMap* HashMap_delete_all_association(HashMap* map);

/*
*restituisce la mappa con inserito il nuovo valore
*/
HashMap* HashMap_insert(HashMap* map, void* key, void* value);

/*
*restituisce 1 se e' vuota 0 altrimenti
*/
int HashMap_isEmpty(HashMap* map);

/*
*restituisce il numero di associazioni
*/
int HashMap_n_associazioni(HashMap* map);

/*
*restituisce 0 se la chiave non è presente 1 altrimenti
*/
int HashMap_isKey(HashMap* map, void* key);

/*
*restituisce il valore associato alla chiave se esiste
* NULL altrimenti
*/
void* HashMap_getValue(HashMap* map, void* key);

/*
* elimina l'assiciazione con quella specifica chiave
* restituisce la mappa modificata
*/
HashMap* HashMap_delete_association(HashMap* map, void* key);

/*
*restituisce un array contenente tutte le chiavi presenti
*/
void** HashMap_getAllKey(HashMap* map);

