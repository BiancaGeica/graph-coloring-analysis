#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 2005

/* Structure to represent an adjacency list node */
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

/* Structure to represent an adjacency list */
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

/* Structure to represent a graph */
typedef struct Graph {
    int N;  /* Number of vertices */
    int M;  /* Number of edges */
    AdjList* array;
    bool adjMatrix[MAXN][MAXN];
    int color[MAXN];
} Graph;

/* Function to create a new adjacency list node */
AdjListNode* createNode(int dest);

/* Function to create a graph with N vertices */
Graph* createGraph(int N, int M);

/* Function to add an edge to an undirected graph */
void addEdge(Graph* graph, int u, int v);

/* Function to free the graph memory */
void freeGraph(Graph* graph);

/* Function to read graph from input */
Graph* readGraph();

#endif /* GRAPH_COLORING_H */
