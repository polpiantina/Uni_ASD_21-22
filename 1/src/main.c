#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

#define INITIAL_CAPACITY 2
#define BUFFER_SIZE 1024

typedef struct _Row {
	int	id_row;		// 4 bytes
	char	*string;	// 8 bytes
	int 	number_i;	// 4 bytes
	double 	number_d;	// 8 bytes
}Row;				// 32 bytes


static int id_cmp(void *r1, void *r2){
	Row *id1 = (Row*)r1;
	Row *id2 = (Row*)r2;
	if(id1->id_row < 0 || id2->id_row < 0) fprintf(stderr, "errore id null");
	return id1->id_row - id2->id_row;
}

static int int_cmp(void *r1, void *r2) {
	Row *i1 = (Row*)r1;
	Row *i2 = (Row*)r2;
	if(i1->number_i < 0 || i2->number_i < 0) fprintf(stderr, "errore int null");
	return i1->number_i - i2->number_i;
}

static int double_cmp(void *r1, void *r2) {
	Row *d1 = (Row*)r1;
	Row *d2 = (Row*)r2;
	if(d1->number_d < 0 || d2->number_d < 0) fprintf(stderr, "errore double null");
	if(d1->number_d < d2->number_d)	return -1;
	if(d1->number_d > d2->number_d)	return 1;
	return 0;
	
}

static int string_cmp(void *r1, void *r2) {
	Row *s1 = (Row*)r1;
	Row *s2 = (Row*)r2;
	if(s1->string == NULL || s2->string == NULL) fprintf(stderr, "errore stringa null");
	return strcmp(s1->string, s2->string);
}

static void array_print(Row *array, unsigned long capacity) {
	for (unsigned long i = 0; i < capacity; i++) {
		printf("\n%10d , %15s , %15d , %16.8f", array[i].id_row, array[i].string, array[i].number_i, array[i].number_d);
	}
}

static Row* array_copy(Row *src, unsigned long capacity) {
	unsigned long i;
	printf("Copying array from original");
	Row* dest = (Row*)malloc(sizeof(Row) * capacity);
	if(dest == NULL) {
		fprintf(stderr, "errore malloc struct array_copy");
		return 0;
	}
	for(i = 0; i < capacity; i++) {
		char* temp_string = malloc(sizeof(char*) * (strlen(src[i].string)));
		int id = src[i].id_row;
		dest[i].id_row = id;
		strcpy(temp_string, src[i].string);
		dest[i].string = temp_string;
		int num_i = src[i].number_i;
		dest[i].number_i = num_i;
		double num_d = src[i].number_d;
		dest[i].number_d = num_d;
		
		if(i%2000000 == 0) {
			printf(".");	//printf("File load currently at %2d%%\n",i/200000);
			fflush(stdout);
		}
	}
	printf("\nArray copy completed\n");
	return dest;
}

static void array_free(Row *csv, unsigned long capacity) {
	unsigned long i;
	printf("Freeing memory...\n");
	for(i = 0; i < capacity; i++) {
		free(csv[i].string);
	}
	free(csv);
	printf("Memory free completed\n");
}

static Row* file_load(FILE *filename, unsigned long *cap){
	char buffer[BUFFER_SIZE];
	unsigned long i;
	unsigned long capacity = *cap;
	
	Row* csv = (Row*)malloc(sizeof(Row) * capacity);
	if(csv == NULL) {
		fprintf(stderr, "errore malloc struct iniziale");
		return 0;
	}
	
	clock_t loadstart = clock();
	printf("Loading file");
	fflush(stdout);
	for(i = 0; fgets(buffer,BUFFER_SIZE,filename) != NULL; i++) { 	// && i<100000	 
		char* riga = malloc(sizeof(char*) * (strlen(buffer)+1));
		if(riga == NULL) {
			fprintf(stderr, "errore malloc riga\n");
			return 0;
		}
		strcpy(riga,buffer);
		char* temp_id = strtok(riga, ",");
		char* temp_string = strtok(NULL, ",");
		char* temp_i = strtok(NULL, ",");
		char* temp_f = strtok(NULL, ",");
		
		char* temp_toRow = malloc(sizeof(char*) * (strlen(temp_string)+1));
		if(temp_toRow == NULL) {
			fprintf(stderr, "errore malloc riga temp\n");
			return 0;
		}
		
		//  --  CHECK PER REALLOC CHE RADDOPPIA  --
		if(i == capacity) {
			capacity *= 2;
			csv = realloc(csv, capacity * sizeof(Row));
			//	printf("\ncapacity -> %ld",capacity);
			if(csv == NULL) {
				fprintf(stderr, "errore realloc a %ld\n", capacity);
				return 0;
			}
		}
		
		csv[i].id_row = atoi(temp_id);
		strcpy(temp_toRow,temp_string);
		csv[i].string = temp_toRow;
		csv[i].number_i = atoi(temp_i);
		csv[i].number_d = atof(temp_f);
		
		//printf("\n%10d , %15s , %15d , %16.8f", csv[i].id_row, csv[i].string, csv[i].number_i, csv[i].number_d);
		if(i%2000000 == 0) {
			printf(".");	//printf("File load currently at %2d%%\n",i/200000);
			fflush(stdout);
		}
		
		free(riga);
	}
	*cap = i;
	printf("\nFile load completed\n");
	//  --  FINE CARICAMENTO RECORD  --
	
	//  --  LOADING TIME TEST  --
	clock_t loadend = clock();
	printf("Time spent loading -> %.2fs\n", (double)(loadend - loadstart) / CLOCKS_PER_SEC);
	fflush(stdout);
	
	//  --  LIBERO MEMORIA INUTILIZZATA IN ECCESSO  --
	csv = realloc(csv, capacity * sizeof(Row));
	if(csv == NULL) {
		fprintf(stderr, "errore realloc finale\n");
		return 0;
	}
	return csv;
}

static int test_bisort_int(Row* csv_og, unsigned long capacity) {
	printf("\n- (INT) -- start\n");
	fflush(stdout);
	Row* csv = array_copy(csv_og, capacity);
	
	printf("Sorting...\n");
	printf("Starting timer for Binary Insertion Sort\n");
	clock_t tstart = clock();
	lib_bisort(csv, sizeof(Row), capacity, int_cmp);
	clock_t tend = clock();
	printf("Time spent for Binary Insertion Sort -> %.2fs\n", (double)(tend - tstart) / CLOCKS_PER_SEC);
	
	printf("Done\n");
	array_free(csv, capacity);
	fflush(stdout);
	return 1;
}

static int test_bisort_string(Row* csv_og, unsigned long capacity) {
	printf("\n- (STRINGS) -- start\n");
	fflush(stdout);
	Row* csv = array_copy(csv_og, capacity);
	
	printf("Sorting...\n");
	printf("Starting timer for Binary Insertion Sort\n");
	clock_t tstart = clock();
	lib_bisort(csv, sizeof(Row), capacity, string_cmp);
	clock_t tend = clock();
	printf("Time spent for Binary Insertion Sort -> %.2fs\n", (double)(tend - tstart) / CLOCKS_PER_SEC);
	
	printf("Done\n");
	
	
	array_print(csv, capacity);
	
	
	array_free(csv, capacity);
	fflush(stdout);
	return 1;
}

static int test_bisort_double(Row* csv_og, unsigned long capacity) {
	printf("\n- (FLOATING POINT) -- start\n");
	fflush(stdout);
	Row* csv = array_copy(csv_og, capacity);
	
	printf("Sorting...\n");
	printf("Starting timer for Binary Insertion Sort\n");
	clock_t tstart = clock();
	lib_bisort(csv, sizeof(Row), capacity, double_cmp);
	clock_t tend = clock();
	printf("Time spent for Binary Insertion Sort -> %.2fs\n", (double)(tend - tstart) / CLOCKS_PER_SEC);
	
	printf("Done\n");
	array_free(csv, capacity);
	fflush(stdout);
	return 1;
}

static void test_qsort_int(Row* csv_og, unsigned long capacity, char pivot) {
	printf("\n- (INT) -- start\n");
	Row* csv = array_copy(csv_og, capacity);
	
	printf("Sorting...\n");
	clock_t qsortstart, qsortend;
	switch(pivot){
		case 'l':
			qsortstart = clock();
			lib_qsort_left_pivot(csv, sizeof(Row), 0, (int)capacity-1, int_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case 'm':
			qsortstart = clock();
			lib_qsort_mid_pivot(csv, sizeof(Row), 0, (int)capacity-1, int_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case 'r':
			qsortstart = clock();
			lib_qsort_right_pivot(csv, sizeof(Row), 0, (int)capacity-1, int_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case '?':
			qsortstart = clock();
			lib_qsort_random_pivot(csv, sizeof(Row), 0, (int)capacity-1, string_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
	}
	
	array_free(csv, capacity);
}

static void test_qsort_double(Row* csv_og, unsigned long capacity, char pivot) {
	printf("\n- (FLOATING POINT) -- start\n");
	Row* csv = array_copy(csv_og, capacity);
	
	printf("Sorting...\n");
	clock_t qsortstart, qsortend;
	switch(pivot){
		case 'l':
			qsortstart = clock();
			lib_qsort_left_pivot(csv, sizeof(Row), 0, (int)capacity-1, double_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case 'm':
			qsortstart = clock();
			lib_qsort_mid_pivot(csv, sizeof(Row), 0, (int)capacity-1, double_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case 'r':
			qsortstart = clock();
			lib_qsort_right_pivot(csv, sizeof(Row), 0, (int)capacity-1, double_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case '?':
			qsortstart = clock();
			lib_qsort_random_pivot(csv, sizeof(Row), 0, (int)capacity-1, string_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
	}
	
	array_free(csv, capacity);
}

static void test_qsort_string(Row* csv_og, unsigned long capacity, char pivot) {
	printf("\n- (STRINGS) -- start\n");
	Row* csv = array_copy(csv_og, capacity);
	
	printf("Sorting...\n");
	clock_t qsortstart, qsortend;
	switch(pivot){
		case 'l':
			qsortstart = clock();
			lib_qsort_left_pivot(csv, sizeof(Row), 0, (int)capacity-1, string_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case 'm':
			qsortstart = clock();
			lib_qsort_mid_pivot(csv, sizeof(Row), 0, (int)capacity-1, string_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case 'r':
			qsortstart = clock();
			lib_qsort_right_pivot(csv, sizeof(Row), 0, (int)capacity-1, string_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
			break;
		case '?':
			qsortstart = clock();
			lib_qsort_random_pivot(csv, sizeof(Row), 0, (int)capacity-1, string_cmp);
			qsortend = clock();
			printf("Time spent sorting -> %.2fs\n", (double)(qsortend - qsortstart) / CLOCKS_PER_SEC);
	}
	
	array_free(csv, capacity);
}

int main(int argc, char** argv){
	unsigned long capacity = INITIAL_CAPACITY;
	
	struct timespec tempo;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tempo);
	srand((unsigned int)tempo.tv_nsec);
	
	if(argc < 3) {
		fprintf(stderr, "errore formattazione, eseguire il file con -> ./nomemain nomefile.csv sortingType (bisort / qsort)\nIn alternativa, si può usare -> make sortingType file=nomefile.csv\n");
		return -1;
	}
	
	if(strcmp(argv[2], "qsort") != 0 && strcmp(argv[2], "bisort") != 0) {
		fprintf(stderr, "errore formattazione, eseguire il file con -> ./nomemain nomefile.csv sortingType (bisort / qsort)\nIn alternativa, si può usare -> make sortingType file=nomefile.csv\n");
		return -1;
	}
	
	FILE *fp = fopen(argv[1], "r");	// presente nella stessa cartella del main
	if(fp == NULL) {
		fprintf(stderr, "errore file\n");
		return -1;
	}
	
	Row *csv = file_load(fp, &capacity);
	if(capacity == 0)	return -1;
	if(csv == NULL) {
		fprintf(stderr, "errore malloc struct iniziale");
		return -1;
	}
	
	//  --  INIZIO ALGORITMI ORDINAMENTO  --
	if(strcmp(argv[2], "bisort") == 0) {
		printf("\n\n[BINARY INSERTION SORT]\n");
			test_bisort_int(csv, capacity);
			test_bisort_double(csv, capacity);
			test_bisort_string(csv, capacity);
		printf("\n-- end\n");
	}
	
	if(strcmp(argv[2], "qsort") == 0) {
		printf("\n\n[QUICKSORT -- LEFT PIVOT]\n");
			test_qsort_int(csv, capacity, 'l');
			test_qsort_double(csv, capacity, 'l');
			test_qsort_string(csv, capacity, 'l');
		printf("\n-- end\n\n");
		
		printf("\n\n[QUICKSORT -- MID PIVOT]\n");
			test_qsort_int(csv, capacity, 'm');
			test_qsort_double(csv, capacity, 'm');
			test_qsort_string(csv, capacity, 'm');
		printf("\n-- end\n\n");
		
		printf("\n\n[QUICKSORT -- RIGHT PIVOT]\n");
			test_qsort_int(csv, capacity, 'r');
			test_qsort_double(csv, capacity, 'r');
			test_qsort_string(csv, capacity, 'r');
		printf("\n-- end\n\n");
		
		printf("\n\n[QUICKSORT -- RANDOM PIVOT]\n");
			test_qsort_int(csv, capacity, '?');
			test_qsort_double(csv, capacity, '?');
			test_qsort_string(csv, capacity, '?');
		printf("\n-- end\n\n");
	}
	array_free(csv, capacity);
	fclose(fp);
	printf("Done\n\n");
	
	return 0;
}
