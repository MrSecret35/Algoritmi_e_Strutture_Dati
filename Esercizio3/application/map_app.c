#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include "hashMap.h"

#define MAX_BUF_LEN 1024
#define SIZE_ARRAY 6321078
#define ERROR_EXIT_CODE 1
#define RANDOM_NUMBER 10000000
#define DIM_MAP 1000000

/*
* Cariva i dati del file args[1] in un HashMap che restituisce
*/
HashMap* load_data_hashMap(int argc, char* argv[]);

/*
* Cariva i dati del file args[1] in un array statico che restituisce
*/
void** load_data_array(int argc, char* argv[]);

/*
* Stampa a video le corrette modalità d'uso
*/
void print_usage();

/*
* funzione di hash 
*/
int hf(int* a){
	return *a%DIM_MAP;
}

/*
* funzione di comparazione
*/
int cmpf(int* a, int* b){
	return *a-*b;
}

/*
* preso un intero restituisce un puntatore equivalente n=*res
*/
int* int_new(int n){
	int* res= (int*)malloc(sizeof(int));
	*res=n;
	return res;
}

/*
* struct utilizzata per memorizzare la coppia
* chiave valore nell'array statico
*/
typedef struct{
	int k;
	int v;
}Coppia;

/*
* funzione di comparazione per coppie
* usata nell'ordinamento
*/
int cmpFun_coppia(Coppia* a, Coppia* b){
	return a->k-b->k;
}

int* load_random_num(int num){
	srand(time(0));
	int* g= (int*)malloc(sizeof(int)*num);
	for (int i = 0; i < num; ++i){
		*(g+i)=rand()%num;
	}
	return g;
}
/*
* algoritmo di merge per l'ordinamento dell'array
*/
void merge(void** a, int left, int center, int right);
void merge_sort(void** a, int left, int right);

/*
* algoritmo di ricerca binaria
* restituisce il valore cercato, -1 altrimenti
*/
int binary_search(void** a, int dim, int key);
int binary_search_rec(void** a, int l, int r, int key);

int main(int argc, char* argv[]){
	clock_t start, end;
	int count1,count2;
	//caricamento dati su hashMap
	printf("Caricamento dati su HashMap\n");
	start = clock();
	HashMap* hashmap=load_data_hashMap(argc, argv);
	end= clock();
	printf("\tTempo impiegato :\t%f secondi\n\n",((double)(end-start)/CLOCKS_PER_SEC));

	//caricamento dati su array
	printf("Caricamento dati su Array statico\n");
	start = clock();
	void** arrayMap=load_data_array(argc, argv);
	merge_sort(arrayMap, 0, SIZE_ARRAY-1);
	end= clock();
	printf("\tTempo impiegato :\t%f secondi\n\n",((double)(end-start)/CLOCKS_PER_SEC));

	//carico RANDOM_NUMBER numeri casuali
	int* keys= load_random_num(RANDOM_NUMBER);

	
	//recupero i dati dalla HashMap
	count1=0;
	printf("Recupero dati su HashMap\n");
	start = clock();
	for (int i = 0; i < RANDOM_NUMBER; ++i){
		int* x= (int*)HashMap_getValue(hashmap,int_new(*(keys+i)));
		if(*x != -1) count1++;
	}
	end= clock();
	printf("\tTempo impiegato :\t%f secondi\n\n",((double)(end-start)/CLOCKS_PER_SEC));

	//recupero i dati dall'array
	printf("Recupero dati su array statico\n");
	count2=0;
	start = clock();
	for (int i = 0; i < RANDOM_NUMBER; ++i){
		int x= binary_search(arrayMap,SIZE_ARRAY,*(keys+i));
		if(x != -1) count2++;
	}
	end= clock();
	printf("\tTempo impiegato :\t%f secondi\n\n",((double)(end-start)/CLOCKS_PER_SEC));

	printf("valori reperiti: HasHMap\tArray\n");
	printf("\t\t%d\t\t%d\n",count1, count2 );
	if (count1 == count2){printf("Recupero avvenuto con SUCCESSO\n");}
	else{printf("Recupero FALLITO\n");}

	HashMap_delete(hashmap);

}

void print_usage(){

	printf("Insert a valid filename(for the records)\n");
}

int binary_search(void** a, int dim, int key){
	if(dim>0){
		return binary_search_rec(a, 0, dim-1, key);
	}else{
		return -1;
	}
	
}
int binary_search_rec(void** a, int l, int r, int k){
	if(r>=l){
		int mid= (l+r)/2;
		if(((Coppia*)a[mid])->k == k){
			return ((Coppia*)a[mid])->v;
		}
		if(((Coppia*)a[mid])->k >k){
			return binary_search_rec(a, l, mid-1, k);
		}else{
			return binary_search_rec(a, mid+1, r, k);
		}
	}
	return -1;
}

void merge(void** a, int left, int center, int right){
	int i=left;
	int j=center+1;
	int k=0;
	void** b= (void**)malloc(sizeof(Coppia)*(right-left+1));

	while(i<=center && j<=right){
		if(cmpFun_coppia(a[i], a[j])<=0){
			b[k]=a[i];
			i++;
		}else{
			b[k]=a[j];
			j++;
		}
		k++;
	}
	while(i<=center ){
		b[k]=a[i];
		i++;

		k++;
	}
	while(j<=right){
		b[k]=a[j];
		j++;
		k++;
	}
	for (k=left; k <= right; k++){
		a[k]=b[k-left];
	}
}

void merge_sort(void** a, int left, int right){
	if(left<right){
		int center= (left+right)/2;
		merge_sort(a, left, center);
		merge_sort(a, center+1 , right);
		merge(a, left, center, right);
	}
}

HashMap* load_data_hashMap(int argc, char* argv[]){
	char buf[MAX_BUF_LEN];
	FILE* file;
	char* token;
	HashMap* g= HashMap_create((hash_function) hf, (cmp_function) cmpf);

	if(argc != 2 ){
		printf("Parameters Error\n");
		print_usage();
		exit(ERROR_EXIT_CODE);
	}
	
	file= fopen(argv[1], "r");
	if(!file){
		printf("Parameters Error\n");
		print_usage();
		exit(ERROR_EXIT_CODE);
	}
	while(fgets(buf,MAX_BUF_LEN,file)){
		//fscanf(file, "%d,%[^,],%d,%f\n",&rec->id, rec->field1, &rec->field2, &rec->field3);
		int K,V;
		token= strtok(buf,",");

		K=atoi(token);
		token= strtok(NULL,",");

		V=atoi(token);

		g=HashMap_insert(g,int_new(K),int_new(V));

		
	}
	return g;
}

void** load_data_array(int argc, char* argv[]){
	char buf[MAX_BUF_LEN];
	FILE* file;
	char* token;
	void** g= (void**)malloc(sizeof(Coppia)*SIZE_ARRAY);
	int count=0;

	if(argc != 2 ){
		printf("Parameters Error\n");
		print_usage();
		exit(ERROR_EXIT_CODE);
	}
	
	file= fopen(argv[1], "r");
	if(!file){
		printf("Parameters Error\n");
		print_usage();
		exit(ERROR_EXIT_CODE);
	}
	count=0;
	while(fgets(buf,MAX_BUF_LEN,file)){
		//fscanf(file, "%d,%[^,],%d,%f\n",&rec->id, rec->field1, &rec->field2, &rec->field3);
		Coppia* t=(Coppia*)malloc(sizeof(Coppia));
		int K,V;
		token= strtok(buf,",");

		K=atoi(token);
		token= strtok(NULL,",");

		V=atoi(token);

		t->k=K;
		t->v=V;

		g[count]=t;

		count++;
	}
	
	return g;
}


