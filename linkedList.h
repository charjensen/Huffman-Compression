typedef struct hnode {
	int value;
	int let;
	struct hnode* lc;
	struct hnode* rc; 
	struct hnode* parent;
} Huffnode;
typedef struct node {
  Huffnode* vnode;
  struct node* next;
} LinkedList;
LinkedList* llCreate();
int llIsEmpty(LinkedList* ll);
void llDisplay(LinkedList* ll);
void llAdd(LinkedList** ll, Huffnode* newValue);
void llFree(LinkedList* ll);
Huffnode* removeFirst(LinkedList** ll);
