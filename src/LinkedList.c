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
    while (node != NULL) {
        LinkedListNode *next = node->next;
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

void *LinkedList_popFront(LinkedList *ll) {
    return LinkedList_remove(ll, ll->head);
}

LinkedListNode *LinkedList_find(LinkedList *ll, void *elem) {
    LinkedListNode *current = ll->head;
    while (current != NULL) {
        if (current->data == elem) {
            return current;
        }
        current = current->next;
    }
    return NULL;
}

void *LinkedList_remove(LinkedList *ll, LinkedListNode *node) {
    if (node == NULL || ll->size == 0) {
        return NULL;
    }

    if (node->prev != NULL) {
        node->prev->next = node->next;
    } else {
        ll->head = node->next;
    }

    if (node->next != NULL) {
        node->next->prev = node->prev;
    } else {
        ll->tail = node->prev;
    }

    void *data = node->data;
    free(node);
    --ll->size;
    return data;
}
