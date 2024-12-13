#include "Graph.h"

#include <stdlib.h>
#include <stdio.h>

Graph *Graph_new(int n) {
    Graph *new_graph = malloc(sizeof(Graph));
    Vertex *arr_vertices = malloc(n * sizeof(Vertex));
    if (new_graph == NULL || arr_vertices == NULL) { return NULL; }
    new_graph->numVertices = n;
    new_graph->numEdges = 0;
    new_graph->vertices = arr_vertices;

    // Initializing vertices
    for (int i = 0; i < n; i++) {
        LinkedList *ll_out = LinkedList_new();
        LinkedList *ll_in = LinkedList_new();
        if (ll_out == NULL || ll_in == NULL) { return NULL; }
        new_graph->vertices[i].id = i;
        new_graph->vertices[i].outNeighbours = ll_out;
        new_graph->vertices[i].inNeighbours = ll_in;
    }

    return new_graph;
}

void Graph_delete(Graph *g) {
    for (int i = 0; i < g->numVertices; i++) {
        LinkedList *ll_in = g->vertices[i].inNeighbours;
        LinkedList_delete(ll_in);
        LinkedList *ll_out = g->vertices[i].outNeighbours;
        LinkedList_delete(ll_out);
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
    Vertex *vertex_i = &g->vertices[i];
    Vertex *vertex_j = &g->vertices[j];
    LinkedListNode *to_be_removed_in = LinkedList_find(vertex_j->inNeighbours, vertex_i);
    LinkedListNode *to_be_removed_out = LinkedList_find(vertex_i->outNeighbours, vertex_j);
    LinkedList_remove(vertex_j->inNeighbours, to_be_removed_in);
    LinkedList_remove(vertex_i->outNeighbours, to_be_removed_out);
    g->numEdges--;
}

Graph *Graph_read(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) { return NULL; }

    int n = 0;
    if (fscanf(file, "%d", &n) != 1) { return NULL; }

    Graph *new_graph = Graph_new(n);
    if (new_graph == NULL) { return NULL; }

    char row[n+1];
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%s", row) != 1) { return NULL; }
        for (int j = 0; j < n; j++) {
            if (row[j] == '1') {
                Graph_addEdge(new_graph, i, j);
            }
        }
    }

    fclose(file);
    return new_graph;
}

void Graph_print(Graph *g) {
    printf("The graph has vertices: %d\n", g->numVertices);
    printf("The graph has edges: %d\n", g->numEdges);

    printf("\nOutgoing edges\n");
    for (int i = 0; i < g->numVertices; i++) {
        Vertex *v = &g->vertices[i];
        printf("%d: ", v->id);
        print_vertices(v->outNeighbours);
    }

    printf("\nIngoing edges\n");
    for (int i = 0; i < g->numVertices; i++) {
        Vertex *v = &g->vertices[i];
        printf("%d: ", v->id);
        print_vertices(v->inNeighbours);
    }
}

void print_vertices(LinkedList *vertices) {
    LinkedListNode *node = vertices->head;
    for (; node != NULL; node = node->next) {
        Vertex *v = node->data;
        printf("%d", v->id);
        if (node->next != NULL) { printf(", "); }
    }
    printf("\n");
}
