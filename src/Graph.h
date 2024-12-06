#ifndef GRAPH_H
#define GRAPH_H

#include "LinkedList.h"

typedef struct Vertex Vertex;
typedef struct Graph Graph;
struct Vertex {
	int id; // a number in [0; numVertices[
	LinkedList *outNeighbours; // A linked list of vertices.
	LinkedList *inNeighbours; // A linked list of vertices
};

struct Graph {
	int numVertices;
	int numEdges;
	Vertex *vertices; // An array of numVertices vertices
};

// Allocates and constructs a new graph with n vertices.
// Returns a pointer to the new graph, or NULL on error.
// Post: the caller owns the graph.
Graph *Graph_new(int n);

// Adds an edge from the i'th to the j'th vertex (0-indexed).
void Graph_addEdge(Graph *g, int i, int j);

// Removes an edge from the i'th to the j'th vertex (0-indexed).
void Graph_removeEdge(Graph *g, int i, int j);

// Reads a graph from the given file and returns a newly
// constructed Graph representing it.
// Returns a pointer to the read graph, or NULL on error.
// Post: the caller owns the graph.
Graph *Graph_read(const char *filename);

// Deallocates the given graph and all its associated memory.
void Graph_delete(Graph *g);

// Prints some useful information about the given graph.
void Graph_print(Graph *g);

#endif // GRAPH_H
