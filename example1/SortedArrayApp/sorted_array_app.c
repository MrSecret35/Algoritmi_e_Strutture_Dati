#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sorted_array.h"

#define ERROR_EXIT_CODE 1
#define MAX_BUF_LEN 1024

typedef struct {
	char* key;
	int val;
} Record;

typedef struct{
	SortedArrayCmp comparison_fun;
	char const* filename;
} Options;

//sorted_array_app < -1 | -2 > <filename>
int compare_first_field(Record* rec1, Record* rec2){
	return strcmp(rec1->key,rec2->key);
}
int compare_second_field(Record* rec1, Record* rec2){
	return rec1->val - rec2->val;
}

void print_usage(){
	printf("sorted arrey app < -1, -2 > <filename>\n");
	printf("    -1: sort according to the first field ascending order \n");
	printf("    -2: sort according to the second field ascending order \n");
}

Options parse_options(int argc, char const *argv[]){
	if(argc != 3 || strlen(argv[1])!= 2 ){
		printf("Parameters Error\n");
		print_usage();
		exit(ERROR_EXIT_CODE);
	}
	Options options;

	if(!strcmp(argv[1], "-1") ){
		options.comparison_fun=(SortedArrayCmp)compare_first_field;
	}else if(!strcmp(argv[1], "-2")){
		options.comparison_fun=(SortedArrayCmp)compare_second_field;
	}else{
		printf("Parameters Error\n");
		print_usage();
		exit(ERROR_EXIT_CODE);
	}

	options.filename=argv[2];
	return options;
}

void load_data(SortedArray* array, char const* filename){
	FILE* file= fopen(filename, "r");

	char buf[MAX_BUF_LEN];
	int val;
	int lineno=0;

	while(!feof(file)){
		Record* record = (Record*)malloc(sizeof(Record));
		int n= fscanf(file, "%[^,],%d\n", buf, &val);
		lineno++;

		if(n!=2){
			if(feof(file)){continue;}
			printf("ERROR while reading file at line %d\n", lineno);
			exit(ERROR_EXIT_CODE);
		}

		record->key= strndup(buf, MAX_BUF_LEN);
		record->val=val;
		SortedArray_insert(array, record);
	}
}

void print_array(SortedArray* array){
	for (int i = 0; i < SortedArray_size(array); ++i){
		Record* rec=SortedArray_get(array,i);
		printf("Key %50s\tval: %10d\n", rec->key,rec->val);
	}
}

void free_data(SortedArray* array){
	for (int i = 0; i < SortedArray_size(array); ++i){
		Record* rec=SortedArray_get(array,i);
		free(rec->key);
		free(rec);
	}
	SortedArray_free(array);
}

int main(int argc, char const *argv[]){

	Options options=parse_options(argc, argv);

	SortedArray* array = SortedArray_new(options.comparison_fun);
	load_data(array, options.filename);
	print_array(array);
	free_data(array);

	return 0;
}