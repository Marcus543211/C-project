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
        for (LinkedListNode *node = u->outNeighbours->head;
                node != NULL; node = node->next) {
            Vertex *v = node->data;
            
            // if v has no other incoming edges than e then
            if (v->inNeighbours->size == 1) {
                // Insert v in S
                LinkedList_append(S, v);
            }

            // Remove edge e from G
            Graph_removeEdge(g, u->id, v->id);
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
        printf("%d", ((Vertex*)node->data)->id);
        for (; node != NULL; node = node->next) {
            printf(", %d", ((Vertex*)node->data)->id);
        }
        printf("\n");
    }

    // Delete the lists.
    LinkedList_delete(L);
    LinkedList_delete(S);
}
