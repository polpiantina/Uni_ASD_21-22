#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

#define MAX_HEIGHT 30

// SUPPORT STRUCTURES

static int int_cmp(void *r1, void *r2) {
	int * i1 = (int *)r1;
	int * i2 = (int *)r2;
	return *i1 - *i2;
}

static int string_cmp(void* v1, void* v2) {
	char *s1 = (char*)v1;
	char *s2 = (char*)v2;
	return strcmp(s1, s2);
}

// TEST UNITS

// checking if the function allows a node as NULL 
void test_node_null(){
    printf("\n[test_node_null]");
    Node * a = createNode(NULL, MAX_HEIGHT);
    assert(NULL != a);
    printf("\nNode exist - OK");
}

// passing 0 just means that it will not have connection to other nodes
void test_node_zero_height(){
    printf("\n\n[test_node_zero_height]");
    Node * a = createNode(NULL, 0);
    assert(NULL != a);
    printf("\nNode exist - OK");
    assert(0 == a->size);
    printf("\nNode has size 0 - OK");
}

// checking if the function can accept a negative value
void test_node_negative_height(){
    long n = -4294967295;
    printf("\n\n[test_node_negative_height]");
    Node * a = createNode(NULL, n); // -4294967295 is implicitly converted to 1
    assert(NULL != a);
    printf("\nNode exist - OK");
    assert((unsigned int)n == a->size);
    printf("\nNode has size equal to the integer value passed - OK");
}

// passing a different compare to check if createList is actually type agnostic
void test_skiplist_generic(){
    printf("\n[test_skiplist_generic]");
    SkipList * a = createList(int_cmp);
    Node * b = createNode(NULL, MAX_HEIGHT);
    assert(NULL != a);
    printf("\nList exist - OK");
    assert(a->head->item == b->item);
    printf("\nElement in list exist - OK");
}

// checking if a null element is accepted
void test_skiplist_insert_null(){
    char * s1 = NULL;
    printf("\n\n[test_skiplist_insert_null]");
    SkipList * a = createList(string_cmp);
    insertSkipList(a, s1);
    printf("\nAdding a NULL element - OK");
}

// checking if a null value breaks something
void test_skiplist_search_null(){
    char s1[] = "hello";
    char s2[] = "bye";
    SkipList * a = createList(string_cmp);
    printf("\n\n[test_skiplist_search_null]");
    insertSkipList(a, (void *)s1);
    printf("\nAdding '%s'",s1);
    insertSkipList(a, (void *)s2);
    printf("\nAdding '%s'",s2);
    assert(-1 == searchSkipList(a, NULL));
    printf("\nNULL value not found - OK");
}

// checking if the function has some type of error catching system
void test_skiplist_free_null(){
    SkipList * a = NULL;
    printf("\n\n[test_skiplist_free_null]");
    freeListMem(a);
    printf("\nPassing NULL gets caught - OK");
}

int main(){
    printf("\n - NODE:");
    test_node_null();
    test_node_zero_height();
    test_node_negative_height();
    
    printf("\n\n - SKIPLIST:");
    test_skiplist_generic();
    test_skiplist_insert_null();
    test_skiplist_search_null();
    test_skiplist_free_null();
    printf("\n\n");
}
