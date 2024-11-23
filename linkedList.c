#include <stdio.h>
#include <stdlib.h> // malloc
#include "linkedList.h"
// typedef struct node {
  // int value;
  // struct node* next;
// } LinkedList;
// LinkedList* llCreate();
// int llIsEmpty(LinkedList* ll);
// void llDisplay(LinkedList* ll);
// void llAdd(LinkedList** ll, int newValue);
// void llFree(LinkedList* ll);

//create new linked list
LinkedList* llCreate() {
  return NULL;
}
//check if its empty
int llIsEmpty(LinkedList* ll) {
  return (ll == NULL);
}
//display each node
void llDisplay(LinkedList* ll) {
  
  LinkedList* p = ll;
  printf("[");
  
  while (p != NULL) {
    printf("%d %c, ", (*p).vnode->value, p->vnode->let);
    p = p->next;
  }
  printf("]\n");
}

//this is add_in_order
void llAdd(LinkedList** ll, Huffnode* newHNode) {
  // Create the new node
  LinkedList* newNode = (LinkedList*)malloc(1 * sizeof(LinkedList));
  newNode->vnode = newHNode;
  newNode->next = NULL;
  
  // Find the end of the list
  LinkedList* p = *ll;
  if (p == NULL) {  // Add first element
    *ll = newNode;  // This is why we need ll to be a **
  } else {
	
	//place node at right spot
	if ( (*ll)->vnode->value > newNode->vnode->value) {

		newNode->next = *ll;
		*ll = newNode;

	}
	else {
    		while (p->next != NULL && (newNode->vnode->value > p->next->vnode->value) ) {
      			p = p->next;
    		}
    	}
    // Attach it to the end
    newNode->next = p->next;
    p->next = newNode;
  }
}

//free each node
void llFree(LinkedList* ll) {
  LinkedList* p = ll;
  while (p != NULL) {
    LinkedList* oldP = p;
    p = p->next;
    free(oldP);
  }
  
}

//unlink first node set the head to the next node and free it
Huffnode* removeFirst(LinkedList** ll) {

	LinkedList* temp = *ll;
	Huffnode* htemp = (*ll)->vnode;
	*ll = (*ll)->next;
	free(temp);

	return htemp;

}