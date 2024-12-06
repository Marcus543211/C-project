#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// A linked list containing any type of pointer.
// The linked list does _not_ own its elements.

typedef struct LinkedList LinkedList;
typedef struct LinkedListNode LinkedListNode;

struct LinkedList {
	LinkedListNode *head;
	LinkedListNode *tail;
	int size;
};

struct LinkedListNode {
	LinkedListNode *next;
	LinkedListNode *prev;
	void *data;
};

// Allocate and initialize an empty linked list.
// Returns: a pointer to the new linked list, or NULL on error.
// Post: the caller owns the linked list.
LinkedList *LinkedList_new();

// Deallocate the given linked list, including all nodes
// (but _not_ the data they point to, the user owns that).
void LinkedList_delete(LinkedList *ll);

// Append a the given element to the list.
// The linked list does _not_ take ownership over the element
// (only the linked list node).
// Returns: a pointer to the node with the new element, or NULL on error.
LinkedListNode *LinkedList_append(LinkedList *ll, void *elem);

// Remove and return the first element from the given list.
// Pre: ll->size != 0
void *LinkedList_popFront(LinkedList *ll);

// Find the linked list node containing the given element.
// Returns: a pointer to the found node, or NULL if the element was not found.
LinkedListNode *LinkedList_find(LinkedList *ll, void *elem);

// Remove the given node from the given linked list (and deallocate it).
// Pre: node must belong to ll
// Returns: node->data
void *LinkedList_remove(LinkedList *ll, LinkedListNode *node);

#endif // LINKEDLIST_H
