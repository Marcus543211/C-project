#include "LinkedList.h"

#include <stdlib.h>

LinkedList *LinkedList_new() {
    LinkedList *ll = malloc(sizeof(LinkedList));
    if (ll == NULL) { return NULL; }
    ll->head = NULL;
    ll->tail = NULL;
    ll->size = 0;
    return ll;
}

void LinkedList_delete(LinkedList *ll) {
    LinkedListNode *node = ll->head;
    LinkedListNode *next = node->next;
    while (node != NULL) {
	next = node->next;
	free(node);
	node = next;
    }
    free(ll);
}

LinkedListNode *LinkedList_append(LinkedList *ll, void *elem) {
    LinkedListNode *node = malloc(sizeof(LinkedListNode));
    if (node == NULL) { return NULL; }
    node->next = NULL;
    node->data = elem;
    if (ll->tail != NULL) {
	ll->tail->next = node;
	node->prev = ll->tail;
	ll->tail = node;
    } else {
	ll->head = ll->tail = node;
	node->prev = NULL;
    }
    ++ll->size;
    return node;
}

