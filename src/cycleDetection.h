#ifndef CYCLEDETECTION_H
#define CYCLEDETECTION_H

#include "Graph.h"

// Runs Kahn's algorithm on the graph, and outputs 'CYCLE DETECTED!\n'
// if a DAG cannot be created, or the vertices as a list fx. '4, 0, 1, 3, 2\n'
// representing an ordering in the DAG.
// The output is printed to stdout.
// The input may be altered in the process.
void cycleDetection(Graph *g);

#endif // CYCLEDETECTION_H
