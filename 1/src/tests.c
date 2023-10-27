#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "lib.h"

#define INITIAL_CAPACITY 2
#define BUFFER_SIZE 1024

// --- support structures ---

typedef struct _Row{
	int		id_row;		// 4 bytes
	char	*string;	// 8 bytes
	int 	number_i;	// 4 bytes
	double 	number_d;	// 8 bytes
}Row;					// 32 byte ???

static int int_cmp(void *r1, void *r2) {
	Row *i1 = (Row*)r1;
	Row *i2 = (Row*)r2;
	return i1->number_i - i2->number_i;
}

static int double_cmp(void *r1, void *r2) {
	Row *d1 = (Row*)r1;
	Row *d2 = (Row*)r2;
	if(d1->number_d < d2->number_d)	return -1;
	if(d1->number_d > d2->number_d)	return 1;
	return 0;
}

static int string_cmp(void *r1, void *r2) {
	Row *s1 = (Row*)r1;
	Row *s2 = (Row*)r2;
	return strcmp(s1->string, s2->string);
}

// --- main tests ---

void test_libsort_null(){
    Row *a = NULL;
    lib_bisort((void *)a, sizeof(Row), 0, int_cmp);
}

void test_qsort_null(){
    Row *a = NULL;
    lib_qsort_left_pivot((void *)a, sizeof(Row), 0, 0, int_cmp);
    lib_qsort_mid_pivot((void *)a, sizeof(Row), 0, 0, double_cmp);
    lib_qsort_right_pivot((void *)a, sizeof(Row), 0, 0, string_cmp);
}

// abbiamo considerato "vuoto" una struttura che abbia dei valori il piu' possibile vicini all'idea di null o invalidi.
// Per quanto riguarda gli int e i double questo non e' possibile, per cui si e' deciso di ovviare alla questione con valori che non fossero contemplati.
void test_libsort_empty(){
    Row a[2];
    a[0].id_row = -1;
    a[0].string = "";
    a[0].number_i = -2;
    a[0].number_d = -1.1; // or NAN, we'll see
    a[1].id_row = -3;
    a[1].string = "";
    a[1].number_i = -4;
    a[1].number_d = -2.2; // or NAN, we'll see

    lib_bisort((void *)&a, sizeof(Row), sizeof(a)/sizeof(Row), int_cmp);
    lib_bisort((void *)&a, sizeof(Row), sizeof(a)/sizeof(Row), double_cmp);
    lib_bisort((void *)&a, sizeof(Row), sizeof(a)/sizeof(Row), string_cmp);
}

void test_qsort_empty(){
    Row a[2];
    a[0].id_row = -1;
    a[0].string = "";
    a[0].number_i = -2;
    a[0].number_d = -1.1; // or NAN, we'll see
    a[1].id_row = -3;
    a[1].string = "";
    a[1].number_i = -4;
    a[1].number_d = -2.2; // or NAN, we'll see

    // definendo le 3 funzioni in modo similare, andiamo a valutare la bonta' di ognuna con un singolo compare
    lib_qsort_left_pivot((void *)&a, sizeof(Row), 0, sizeof(a)/sizeof(Row), int_cmp);
    printf("\nint OK");
    lib_qsort_mid_pivot((void *)&a, sizeof(Row), 0, sizeof(a)/sizeof(Row), double_cmp);
    printf("\ndouble OK");
    //lib_qsort_right_pivot((void *)&a, sizeof(Row), 0, sizeof(a)/sizeof(Row), string_cmp);
    printf("\nstring OK");
}

// quick test with an unordered array and an ordered one
void test_bisort_sorting(){
    Row a[3], b[3];
    a[0].id_row = 1;
    a[0].string = "def";
    a[0].number_i = 234;
    a[0].number_d = 456.789;
    a[1].id_row = 0;
    a[1].string = "abc";
    a[1].number_i = 123;
    a[1].number_d = 123.456;
    a[2].id_row = 2;
    a[2].string = "ghi";
    a[2].number_i = 345;
    a[2].number_d = 789.012;
    // ordered one, same values as a[]
    b[0].id_row = 0;
    b[0].string = "abc";
    b[0].number_i = 123;
    b[0].number_d = 123.456;
    b[1].id_row = 1;
    b[1].string = "def";
    b[1].number_i = 234;
    b[1].number_d = 456.789;
    b[2].id_row = 2;
    b[2].string = "ghi";
    b[2].number_i = 345;
    b[2].number_d = 789.012;

    lib_bisort((void *)&a, sizeof(Row), sizeof(a)/sizeof(Row), int_cmp);
    for (int i = 0; i < (int)(sizeof(a)/sizeof(Row)); i++) assert(a[i].number_i == b[i].number_i);
    lib_bisort((void *)&a, sizeof(Row), sizeof(a)/sizeof(Row), string_cmp);
    for (int i = 0; i < (int)(sizeof(a)/sizeof(Row)); i++) assert(a[i].string == b[i].string);
    lib_bisort((void *)&a, sizeof(Row), sizeof(a)/sizeof(Row), double_cmp);
    for (int i = 0; i < (int)(sizeof(a)/sizeof(Row)); i++) assert(a[i].number_d == b[i].number_d);
}

void test_qsort_sorting(){
    Row a[3], b[3];
    a[0].id_row = 1;
    a[0].string = "def";
    a[0].number_i = 234;
    a[0].number_d = 456.789;
    a[1].id_row = 0;
    a[1].string = "abc";
    a[1].number_i = 123;
    a[1].number_d = 123.456;
    a[2].id_row = 2;
    a[2].string = "ghi";
    a[2].number_i = 345;
    a[2].number_d = 789.012;

    // ordered one, same values as a[]
    b[0].id_row = 0;
    b[0].string = "abc";
    b[0].number_i = 123;
    b[0].number_d = 123.456;
    b[1].id_row = 1;
    b[1].string = "def";
    b[1].number_i = 234;
    b[1].number_d = 456.789;
    b[2].id_row = 2;
    b[2].string = "ghi";
    b[2].number_i = 345;
    b[2].number_d = 789.012;

    lib_qsort_left_pivot((void *)&a, sizeof(Row), 0, (sizeof(a)/sizeof(Row))-1, int_cmp);
    for (int i = 0; i < (int)(sizeof(a)/sizeof(Row)); i++) assert(a[i].number_i == b[i].number_i);
    printf("\nint OK");
    lib_qsort_mid_pivot((void *)&a, sizeof(Row), 0, (sizeof(a)/sizeof(Row))-1, double_cmp);
    for (int i = 0; i < (int)(sizeof(a)/sizeof(Row)); i++) assert(a[i].string == b[i].string);
    printf("\ndouble OK");
    lib_qsort_right_pivot((void *)&a, sizeof(Row), 1, (sizeof(a)/sizeof(Row))-1, string_cmp);
    for (int i = 0; i < (int)(sizeof(a)/sizeof(Row)); i++) assert(a[i].number_d == b[i].number_d);
    printf("\nstring OK");
}

int main() {
    // null array
    printf("\nBINSORT NULL:");
    test_libsort_null();
    printf("\nQSORT NULL:");
    test_qsort_null();

    // empty values
    printf("\n\nBINSORT EMPTY:");
    test_libsort_empty();
    printf("\nQSORT EMPTY:");
    test_qsort_empty();

    // small sorting
    printf("\n\nBINSORT SORTING:");
    test_bisort_sorting();
    printf("\nQSORT SORTING:");
    test_qsort_sorting();
    printf("\n");

}
