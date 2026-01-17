#ifndef GRAPH_COLORING_H
#define GRAPH_COLORING_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAXN 2005

/* Structura pentru a reprezenta un nod din lista de adiacenta */
typedef struct AdjListNode {
    int dest;
    struct AdjListNode* next;
} AdjListNode;

/* Structura pentru a reprezenta o lista de adiacenta */
typedef struct AdjList {
    AdjListNode* head;
} AdjList;

/* Structura pentru a reprezenta un graf */
typedef struct Graph {
    int N;  /* Numarul de noduri */
    int M;  /* Numarul de muchii */
    AdjList* array;
    bool adjMatrix[MAXN][MAXN];
    int color[MAXN];
} Graph;

/* Functie pentru a crea un nou nod in lista de adiacenta */
AdjListNode* createNode(int dest);

/* Functie pentru a crea un graf cu N noduri */
Graph* createGraph(int N, int M);

/* Functie pentru a adauga o muchie intr-un graf neorientat */
void addEdge(Graph* graph, int u, int v);

/* Functie pentru a elibera memoria grafului */
void freeGraph(Graph* graph);

/* Functie pentru a citi graful de la intrare */
Graph* readGraph();

#endif /* GRAPH_COLORING_H */