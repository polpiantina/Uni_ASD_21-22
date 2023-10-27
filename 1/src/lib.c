#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "lib.h"

//  --  SEZIONE BISORT  --  con funzione di binsearch
static int lib_binsearch(void *array, unsigned long size, int low, int val_pos, int (*compare)(void*, void*)) {
	//  --  low deve partire da 0		high deve partire da pos attuale -1  --
	char *arr = (char*)array;
	int high = val_pos - 1;
	while (low <= high) {
		int mid = low + (high - low) / 2;
		if(compare(arr+(val_pos*((int)size)), arr+(mid*((int)size))) == 0)		   return mid + 1;
		else if(compare(arr+(val_pos*((int)size)), arr+(mid*((int)size))) > 0)	   low =  mid + 1;
		else									high = mid - 1;
	}
	return low;
}

void lib_bisort(void *array, unsigned long size, unsigned long capacity, int (*compare)(void*, void*)) {
	if(array == NULL){
		printf("\nThe pointer points to nothing.");
	}else{
		char *arr = (char*)array;
		for(int i = 0; i < (int)capacity; i++) {
			int start = lib_binsearch((void*)arr, size, 0, i, compare);
			int j = i;
			void *temp = malloc(size);
			memcpy(temp, arr+(i*((int)size)), size);
			while(j > start) {		// la prima iterazione start = j = 0
				memcpy(arr+(j*((int)size)), arr+((j-1)*((int)size)), size);
				j--;
			}
			memcpy(arr+(start*((int)size)), temp, size);
			free(temp);
		}
	}
}
//  --  FINE SEZIONE BISORT  --

//  --  SEZIONE QSORT  --
/* Qsort support function that swaps two records */
static void lib_swap(void *p1, void *p2, unsigned long size) {
	char pt[size];			// uso questo invece di una malloc perché è più rapido
	memcpy(pt, p1, size);	// dest, source, size
	memcpy(p1, p2, size);
	memcpy(p2, pt, size);
}

static int partition_left_pivot_hoare(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)) {
	char *arr = (char*)array;
	int i, j;
	char temp[size];
	memcpy(temp, arr + ((unsigned long)left * size), size);
	i = left - 1;
	j = right + 1;
	while(1) {
		do	i++;	while((*compare)((arr + ((unsigned long)i * size)), (void*)temp) < 0);
		do	j--;	while((*compare)((arr + ((unsigned long)j * size)), (void*)temp) > 0);
		if(i >= j)	return j;
		lib_swap((arr + ((unsigned long)i * size)), (arr + ((unsigned long)j * size)), size);
	}
	return -1;
}

static int partition_mid_pivot_hoare(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)) {
	char *arr = (char*)array;
	int i, j;
	char temp[size];
	memcpy(temp, arr + (((unsigned long)(left+right)/2) * size), size);
	i = left - 1;
	j = right + 1;
	while(1) {
		do	i++;	while((*compare)((arr + ((unsigned long)i * size)), (void*)temp) < 0);
		do	j--;	while((*compare)((arr + ((unsigned long)j * size)), (void*)temp) > 0);
		if(i >= j)	return j;
		lib_swap((arr + ((unsigned long)i * size)), (arr + ((unsigned long)j * size)), size);
	}
	return -1;
}

static int partition_right_pivot_hoare(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)) {
	char *arr = (char*)array;
	int i, j;
	char temp[size];
	memcpy(temp, arr + ((unsigned long)right * size), size);
	i = left - 1;
	j = right + 1;
	while(1) {
		do	i++;	while((*compare)((arr + ((unsigned long)i * size)), (void*)temp) < 0);
		do	j--;	while((*compare)((arr + ((unsigned long)j * size)), (void*)temp) > 0);
		if(i >= j)	return j;
		lib_swap((arr + ((unsigned long)i * size)), (arr + ((unsigned long)j * size)), size);
	}
	return -1;
}

static int partition_random_pivot_hoare(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)) {
	char *arr = (char*)array;
	int i, j;
	char temp[size];
	
	memcpy(temp, arr + ((unsigned long)(left + (rand() % (right-left))) * size), size);
	i = left - 1;
	j = right + 1;
	while(1) {
		do	i++;	while((*compare)((arr + ((unsigned long)i * size)), (void*)temp) < 0);
		do	j--;	while((*compare)((arr + ((unsigned long)j * size)), (void*)temp) > 0);
		if(i >= j)	return j;
		lib_swap((arr + ((unsigned long)i * size)), (arr + ((unsigned long)j * size)), size);
	}
	return -1;
}

void lib_qsort_left_pivot(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)){
	if(array == NULL){
		printf("\nThe pointer points to nothing.");
	}else{
		if (left >= right) return;
		int i = partition_left_pivot_hoare(array, size, left, right, compare);
		lib_qsort_left_pivot(array, size, left, i-1, compare);
		lib_qsort_left_pivot(array, size, i+1, right, compare);
	}
}

void lib_qsort_mid_pivot(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)) {
	if(array == NULL){
		printf("\nThe pointer points to nothing.");
	}else{
		if (left >= right) return;
		int i = partition_mid_pivot_hoare(array, size, left, right, compare);
		lib_qsort_mid_pivot(array, size, left, i-1, compare);
		lib_qsort_mid_pivot(array, size, i+1, right, compare);
	}
}

void lib_qsort_right_pivot(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)) {
	if(array == NULL){
		printf("\nThe pointer points to nothing.");
	}else{
		if (left >= right) return;
		int i = partition_right_pivot_hoare(array, size, left, right, compare);
		lib_qsort_right_pivot(array, size, left, i-1, compare);
		lib_qsort_right_pivot(array, size, i+1, right, compare);
	}
}

void lib_qsort_random_pivot(void *array, unsigned long size, int left, int right, int (*compare)(void*, void*)) {
	if(array == NULL){
		printf("\nThe pointer points to nothing.");
	}else{
		if (left >= right) return;
		int i = partition_random_pivot_hoare(array, size, left, right, compare);
		lib_qsort_random_pivot(array, size, left, i-1, compare);
		lib_qsort_random_pivot(array, size, i+1, right, compare);
	}
}

