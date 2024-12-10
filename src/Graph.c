#include "Graph.h"
#include <stdlib.h>
#include "LinkedList.h"
#include <stdio.h>

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

Graph *Graph_read(const char *filename) {
    FILE *file = fopen (filename, "r");
    int n = 0;
    if (fscanf(file, "%d", &n) != 1) { return NULL; }
    char row[n+1];
    Graph *new_graph = Graph_new(n);
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%s", row) != 1) { return NULL; }
        for (int j = 0; j < n; j++) {
            int test = row[j] - '0';
            if (test == 1) {
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
        printf("%d: ", i);
        Vertex *v = &g->vertices[i];
        LinkedListNode *node = v->outNeighbours->head;
        for (; node != NULL; node = node->next) {
            printf("%d, ", ((Vertex*)node->data)->id);
            if (node->next != NULL) { printf(", "); }
        }
        printf("\n");
    }

    printf("\nIngoing edges\n");
    for (int i = 0; i < g->numVertices; i++) {
        printf("%d: ", i);
        Vertex *v = &g->vertices[i];
        LinkedListNode *node = v->inNeighbours->head;
        for (; node != NULL; node = node->next) {
            printf("%d, ", ((Vertex*)node->data)->id);
            if (node->next != NULL) { printf(", "); }
        }
        printf("\n");
    }
}
