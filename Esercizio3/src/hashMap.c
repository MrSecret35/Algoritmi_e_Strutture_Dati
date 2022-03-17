#include<stdlib.h>
#include <stdio.h>

#include "hashMap.h"

struct _Record{
	void* K;
	void* V;
	void* succ;
};

struct _HashMap{
	void** array;
	int capacity;
	hash_function hashF;
	cmp_function cmpKey;
};

HashMap* HashMap_create(hash_function Fun, cmp_function cmp){
	HashMap* d=(HashMap*)malloc(sizeof(HashMap));
	d->capacity=1;
	d->hashF=Fun;
	d->cmpKey=cmp;
	d->array= (void**)malloc(d->capacity*sizeof(Record));
	d->array[0]=NULL;
	return d;
}

void HashMap_delete(HashMap* map){
	for (int i = 0; i < map->capacity; ++i){
		dealloc_list(map->array[i]);
	}
	free(map->array);
	free(map);
}

void dealloc_list(Record* rec){
	if(rec==NULL || rec->succ==NULL){
		free(rec);
	}else{
		dealloc_list(rec->succ);
		free(rec);
	}
}

HashMap* HashMap_delete_all_association(HashMap* map){
	for (int i = 0; i < map->capacity; ++i){
		dealloc_list(map->array[i]);
		map->array[i]=NULL;
	}
	return map;
}

HashMap* HashMap_insert(HashMap* map, void* key, void* value){
	int ind= map->hashF(key);
	Record* rec=(Record*)malloc(sizeof(Record));
	rec->K=key;
	rec->V=value;
	rec->succ=NULL;

	if(HashMap_isKey(map,key)==1){// chiave gia' esistente
		return map;
	}
	if(ind >= map->capacity){
		int i=map->capacity;
		map->capacity=ind+1;
		map->array= (void**)realloc(map->array,map->capacity*sizeof(Record));
		for(i=i; i < map->capacity; ++i){
			map->array[i]=NULL;
		}
	}
	if(map->array[ind]== NULL){
		map->array[ind]=rec;
	}else{
		Record* tmp=map->array[ind];
		if(map->cmpKey(tmp->K,key)>=0){
			rec->succ=tmp;
			map->array[ind]=rec;
		}else{
			while(tmp->succ!=NULL && map->cmpKey(((Record*)tmp->succ)->K,key)<0){
				tmp=tmp->succ;
			} 
			rec->succ=tmp->succ;
			tmp->succ=rec;
		}
	}
	
	return map;

	
}

int HashMap_isEmpty(HashMap* map){
	int x=0;
	for (int i = 0; i < map->capacity; ++i){
		Record* rec1=map->array[i];
		while(rec1 != NULL){
			x++;
			rec1=rec1->succ;
		}
	}
	if(x>0){ return 0;}
	else {return 1;}
}

int HashMap_n_associazioni(HashMap* map){
	int x=0;
	for (int i = 0; i < map->capacity; ++i){
		Record* rec1=map->array[i];
		while(rec1 != NULL){
			x++;
			rec1=rec1->succ;
		}
	}
	return x;
}

int HashMap_isKey(HashMap* map, void* key){
	int ris=0;
	int ind=map->hashF(key);
	if(ind< map->capacity){
		Record* tmp=map->array[ind];
		if(tmp!= NULL){
			if(map->cmpKey(tmp->K,key)==0){ ris=1;}
			while(tmp->succ!=NULL && ris!=1 && map->cmpKey(tmp->K,key)<0){
				if(map->cmpKey(tmp->K,key)==0){ ris=1;}
				tmp=tmp->succ;
			} 
		}
	}
	
	return ris;

}

void* HashMap_getValue(HashMap* map, void* key){
	int ind=map->hashF(key);
	if(ind< map->capacity){
		Record* tmp=map->array[ind];
		while(tmp!= NULL && map->cmpKey(tmp->K,key)<=0){
			if(map->cmpKey(tmp->K,key)==0) return tmp->V;
			tmp=tmp->succ;
		}
	}
	int* x;
	*x=-1;
	return x;
}

HashMap* HashMap_delete_association(HashMap* map, void* key){
	if(HashMap_isKey(map,key)==1){
		int ind=map->hashF(key);
		Record* tmp=map->array[ind];
		if(map->cmpKey(tmp->K,key)==0){
			map->array[ind]=tmp->succ;
		}else{
			while(tmp->succ != NULL){
				Record* tmp1=tmp->succ;
				if(map->cmpKey(tmp1->K,key)==0){
					Record* el=tmp1;
					tmp->succ=tmp1->succ;
					free(el);
					return map;
				}
				tmp=tmp->succ;
			}
		}
	}
	return map;
}

void** HashMap_getAllKey(HashMap* map){
	void** t= (void**)malloc(sizeof(void*)*HashMap_n_associazioni(map));
	int j=0;
	for (int i = 0; i < map->capacity; ++i){
		Record* rec1=map->array[i];
		while(rec1 != NULL){
			t[j]=rec1->K;
			j++;
			rec1=rec1->succ;
		}
	}
	return t;
}