#include "cycleDetection.h"

#include <stddef.h>
#include <stdio.h>
#include "Graph.h"
#include "LinkedList.h"

void cycleDetection(Graph *g) {
    // L <- an empty list of vertices
    LinkedList *L = LinkedList_new();
    if (L == NULL) { return; }

    // S <- a set of all vertices of G with no incoming edges
    LinkedList *S = LinkedList_new();
    if (S == NULL) { return; }

    for (int i = 0; i < g->numVertices; i++) {
        Vertex *vertex = &g->vertices[i];
        if (vertex->inNeighbours->size == 0) {
            LinkedList_append(S, vertex);
        }
    }

    // while S is non-empty do
    while (S->size > 0) {
        // u <- a node removal from S
        Vertex *u = LinkedList_popFront(S);

        // Append u to tail of L
        LinkedList_append(L, u);

        // foreach vertex v in G with an edge e from u to v do
        // (I.e., the outgoing edges from u)
        LinkedListNode *node = u->outNeighbours->head;
        while (node != NULL) {
            Vertex *v = node->data;
            
            // if v has no other incoming edges than e then
            if (v->inNeighbours->size == 1) {
                // Insert v in S
                LinkedList_append(S, v);
            }

            // Get the next node before removing "node"
            LinkedListNode *next = node->next;
            
            // Remove edge e from G
            // (This invalidates "node")
            Graph_removeEdge(g, u->id, v->id);

            // Move to next node
            node = next;
        }
    }

    // if G has any edges left then
    if (g->numEdges > 0) {
        // return error // At least one cycle
        printf("CYCLE DETECTED!\n");
    // else
    } else {
        // return L // a topological sorted order of the vertices
        LinkedListNode *node = L->head;
        for (; node != NULL; node = node->next) {
            printf("%d", ((Vertex*)node->data)->id);
            if (node->next != NULL) { printf(", "); }
        }
        printf("\n");
    }

    // Delete the lists.
    LinkedList_delete(L);
    LinkedList_delete(S);
}

