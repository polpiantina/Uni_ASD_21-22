#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib.h"

#define MAX_HEIGHT 20

Node* createNode(void* elem, unsigned int lvls) {
	Node *n = (Node*)malloc(sizeof(Node));
	
	n->next = (Node**)malloc(lvls * sizeof(Node*));
	for(unsigned int i = 0; i < lvls; i++) {
		n->next[i] = NULL;
	}
	n->size = lvls;
	n->item = elem;
	
	return n;
}

SkipList* createList(int (*compare)(void*, void*)) {
	SkipList *list = (SkipList*)malloc(sizeof(SkipList));
	list->head = createNode(NULL, MAX_HEIGHT);
	list->max_level = 0;
	list->compare = compare;
	return list;
}

void freeListMem(SkipList* list) {
	if(list == NULL) return;
	Node *temp, *n = list->head;
	while(n != NULL) {
		temp = n->next[0];
		free(n->item);
		free(n->next);
		free(n);
		n = temp;
	}
	free(list);
}

static unsigned int randomLevel() {
	unsigned int lvl = 1;
	struct timespec tempo;
	clock_gettime(CLOCK_MONOTONIC_RAW, &tempo);
	srand((unsigned int)tempo.tv_nsec);				// uso i nanosecondi per assicurarmi una buona varietà di altezze, coi millisecondi si creano blocchi di altezze uguali
	
	// rand() returns a random value in [0...1)
	while(((rand()%100) < 50) && (lvl < MAX_HEIGHT))	lvl++;
	return lvl;
}

void insertSkipList(SkipList* list, void* elem) {
	if(elem == NULL) return;
	Node *new = createNode(elem, randomLevel());
	if(new->size > list->max_level)		list->max_level = new->size;
	Node *x = list->head;
	for(int k = ((int)(list->max_level))-1; k >= 0; k--) {
		if(x->next[k] == NULL || list->compare(elem, x->next[k]->item) < 0) {
			if(k < (int)new->size) {
				new->next[k] = x->next[k];
				x->next[k] = new;
			}
		} else {
			x = x->next[k];
			k++;
		}
	}	
}

int searchSkipList(SkipList* list, void* elem) {	// return 1 if element is found
	if(elem == NULL) return -1;
	Node *x = list->head;

	// loop invariant: x.item < I
	for(int i = (int)list->max_level-1; i >= 0; i--) {								// mi sposto in verticale
		while(x->next[i] != NULL && list->compare(x->next[i]->item, elem) < 0) {	// mi sposto in orizzontale
			x = x->next[i];
		}
	}
	
	x = x->next[0];
	if(x == NULL || list->compare(x->item,elem) != 0)	return -1;
	else												return 1;
}
