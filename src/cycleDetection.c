#include "cycleDetection.h"

#include <stddef.h>
#include <stdio.h>
#include "Graph.h"

void cycleDetection(Graph *g) {
    // The list to sort into
    LinkedList *L = LinkedList_new();
    if (L == NULL) { return; }

    // The list of all vertices of G with no incoming edges
    LinkedList *S = LinkedList_new();
    if (S == NULL) { return; }

    // Add the vertices with no incoming edges to S 
    for (int i = 0; i < g->numVertices; i++) {
        Vertex *vertex = &g->vertices[i];
        if (vertex->inNeighbours->size == 0) {
            LinkedList_append(S, vertex);
        }
    }

    while (S->size > 0) {
        Vertex *u = LinkedList_popFront(S);
        LinkedList_append(L, u);

        LinkedListNode *node = u->outNeighbours->head;
        while (node != NULL) {
            Vertex *v = node->data;
            
            // When v has no incoming edges other than from u
            if (v->inNeighbours->size == 1) {
                LinkedList_append(S, v);
            }

            // Get the next node before removing "node"
            LinkedListNode *next = node->next;
            // Remove the edge from u to v (This invalidates "node")
            Graph_removeEdge(g, u->id, v->id);
            node = next;
        }
    }

    // if G has any edges left then a cycle exists
    if (g->numEdges > 0) {
        printf("CYCLE DETECTED!\n");
    } else {
        // L is now a topological sorted order of the vertices
        print_vertices(L);
    }

    LinkedList_delete(L);
    LinkedList_delete(S);
}
