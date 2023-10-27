#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include "lib.h"

#define BUFFER_SIZE 1024

static int string_cmp(void* v1, void* v2) {
	char *s1 = (char*)v1;
	char *s2 = (char*)v2;
	return strcmp(s1, s2);
}

static void listFill(FILE *filename, SkipList *list) {
	char buffer[BUFFER_SIZE];
	unsigned long i;
	
	printf("Loading SkipList");
	clock_t loadstart = clock();
	for(i = 0; fgets(buffer,BUFFER_SIZE,filename) != NULL; i++) {
		char* riga = malloc(sizeof(char) * (strlen(buffer)+1));
		if(riga == NULL) {
			fprintf(stderr, "errore malloc riga\n");
			return;
		}
		
		strcpy(riga,buffer);
		riga[strlen(riga)-1] = '\0';	// devo aggiungerlo per assicurarmi che le stringhe di dictionary e correctme abbiano la stessa formattazione
		
		insertSkipList(list, (void*)(riga));
		
		if(i % 60000 == 0){
			printf(".");
			fflush(stdout);
		}
	}
	clock_t loadend = clock();
	printf("\nSkipList load completed\n");
	//  --  FINE CARICAMENTO RECORD  --
	
	//  --  LOADING TIME TEST  --
	printf("Time spent loading -> %.2fs\n", (double)(loadend - loadstart) / CLOCKS_PER_SEC);
	fflush(stdout);
}

static void listPrint(SkipList* list) {
	printf("\nPrinting Items info:\n");
	Node *tmp = list->head;
	int i = 0;
	while(tmp != NULL) {	// stampa anche la testa
		printf("%8d  --  Item: %15s  --  Height: %d\n", i++, (char*)(tmp->item), tmp->size);
		tmp = tmp->next[0];
	}
}

static char* wordRead(FILE *fp) {
	char word[99];
	int letter = 0, i = 0;
	
	while(isalpha(letter) == 0 && letter != EOF)	letter = fgetc(fp);
	while(isalpha(letter) != 0 && letter != EOF) {
		word[i] = (char)tolower(letter);
		i++;
		letter = fgetc(fp);
	}
	word[i] = '\0';
	if(letter == EOF)	return NULL;
	char *w = (char*)malloc(sizeof(char) * (unsigned int)(i+1));
	strcpy(w, word);
	return w;
}

static void wordsFind(FILE *fp, SkipList *list) {
	char* word = wordRead(fp);
	while(word != NULL) {
		if(searchSkipList(list, (void*)word) == -1)		printf("Word not found -> %s\n", word);
		free(word);
		word = wordRead(fp);
	}
}

int main(int argc, char** argv){
	
	if(argc < 3) {
		fprintf(stderr, "errore formattazione, eseguire il file con -> ./nomemain dictionary.txt correctme.txt\nIn alternativa, si può usare -> make run dict=nomefile.txt file=nomefile.txt\n");
		return -1;
	}
	
	FILE *dictionary = fopen(argv[1], "r");	// presente in src/
	if(dictionary == NULL) {
		fprintf(stderr, "errore file dizionario\n");
		return -1;
	}
	
	FILE *correctme = fopen(argv[2], "r");	// presente in src/
	if(correctme == NULL) {
		fprintf(stderr, "errore file di testo\n");
		return -1;
	}
	
	SkipList *list = createList(string_cmp);
	
	listFill(dictionary, list);
	fclose(dictionary);
	
	//	listPrint(list);
	
	printf("\nStarting words search...\n");
	clock_t searchstart = clock();
	wordsFind(correctme, list);
	clock_t searchend = clock();
	printf("Words search done\n");
	printf("Time spent searching  -> %.8fs\n", (double)(searchend - searchstart) / CLOCKS_PER_SEC);
	fflush(stdout);
	
	fclose(correctme);
	
	freeListMem(list);
	printf("\n");
	return 0;
}
