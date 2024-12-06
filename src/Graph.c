#include "Graph.h"
#include <stdlib.h>
#include "LinkedList.h"

Graph *Graph_new(int n) {
    Graph *New_Graph = (Graph*)malloc(sizeof(Graph));
    Vertex *arr_vertices = (Vertex*)malloc(n * sizeof(Vertex));
    if (New_Graph == NULL || arr_vertices == NULL) { return NULL; }
    New_Graph->numVertices = n;
    New_Graph->numEdges = 0;
    New_Graph->vertices = arr_vertices;

    for (int i = 0; i < n; i++) {
        LinkedList *llout = LinkedList_new();
        LinkedList *llin = LinkedList_new();
        if (llout == NULL || llin == NULL) { return NULL; }
        New_Graph->vertices[i].id = i;
        New_Graph->vertices[i].outNeighbours = llout;
        New_Graph->vertices[i].inNeighbours = llin;
    }
    return New_Graph;
}

void Graph_delete(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        LinkedList *llin = g->vertices[i].inNeighbours;
        LinkedList_delete(llin);
        LinkedList *llout = g->vertices[i].outNeighbours;
        LinkedList_delete(llout);
    }
    free(g->vertices);
    free(g);
}

void Graph_addEdge(Graph *g, int i, int j) {
    LinkedList_append(g->vertices[i].outNeighbours, &g->vertices[j]);
    LinkedList_append(g->vertices[j].inNeighbours, &g->vertices[i]);
    g->numEdges++;
}

void Graph_removeEdge(Graph *g, int i, int j) {
    Vertex *Vertex_i = &g->vertices[i];
    Vertex *Vertex_j = &g->vertices[j];
    LinkedListNode *to_be_removedin = LinkedList_find(Vertex_j->inNeighbours, Vertex_i);
    LinkedListNode *to_be_removedout = LinkedList_find(Vertex_i->outNeighbours, Vertex_j);
    LinkedList_remove(Vertex_j->inNeighbours, to_be_removedin);
    LinkedList_remove(Vertex_i->outNeighbours, to_be_removedout);
    g->numEdges--;
}