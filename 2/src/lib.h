typedef struct _SkipList SkipList;
typedef struct _Node Node;

struct _SkipList {
	Node *head;						// first node
	unsigned int max_level;			// max height
	int (*compare)(void*, void*);
};

struct _Node {
	Node **next;				// array di puntatori in avanti (potrei puntare a più posizioni in avanti)
	unsigned int size;			// num di posizioni di next
	void *item;					// l'elemento generico -- valore del nodo (?)
};

SkipList* createList(int (*compare)(void*, void*)); // create a new skiplist and set the default values to its fields
Node* createNode(void*, unsigned int); // create a new node and allocate the space needed for other nodes based on the levels
void insertSkipList(SkipList*, void*); // add to the skiplist the node in the right position
int searchSkipList(SkipList*, void*); // search in the skiplist the element passed as parameter and return 1 if found, -1 otherwise
void freeListMem(SkipList*); // free the pointer(s) to the skiplist passed as parameter
