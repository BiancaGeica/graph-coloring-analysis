#include "graph_coloring.h"

/* Function to create a new adjacency list node */
AdjListNode* createNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

/* Function to create a graph with N vertices */
Graph* createGraph(int N, int M) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->N = N;
    graph->M = M;
    graph->array = (AdjList*)malloc(N * sizeof(AdjList));
    
    /* Initialize adjacency lists and matrices */
    for (int i = 0; i < N; i++) {
        graph->array[i].head = NULL;
        graph->color[i] = 0;
        for (int j = 0; j < N; j++) {
            graph->adjMatrix[i][j] = false;
        }
    }
    
    return graph;
}

/* Function to add an edge to an undirected graph */
void addEdge(Graph* graph, int u, int v) {
    /* Add edge from u to v */
    AdjListNode* newNode = createNode(v);
    newNode->next = graph->array[u].head;
    graph->array[u].head = newNode;
    
    /* Add edge from v to u (undirected) */
    newNode = createNode(u);
    newNode->next = graph->array[v].head;
    graph->array[v].head = newNode;
    
    /* Update adjacency matrix */
    graph->adjMatrix[u][v] = true;
    graph->adjMatrix[v][u] = true;
}

/* Function to free the graph memory */
void freeGraph(Graph* graph) {
    if (graph) {
        for (int i = 0; i < graph->N; i++) {
            AdjListNode* current = graph->array[i].head;
            while (current) {
                AdjListNode* temp = current;
                current = current->next;
                free(temp);
            }
        }
        free(graph->array);
        free(graph);
    }
}

/* Function to read graph from input */
Graph* readGraph() {
    int N, M;
    scanf("%d %d", &N, &M);
    
    Graph* graph = createGraph(N, M);
    
    for (int i = 0; i < M; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }
    
    return graph;
}

/* Check if current color assignment is safe for vertex v */
bool isSafeBacktrack(Graph* graph, int v, int c) {
    AdjListNode* current = graph->array[v].head;
    
    /* Check all adjacent vertices */
    while (current) {
        int u = current->dest;
        if (graph->color[u] == c) {
            return false;
        }
        current = current->next;
    }
    
    return true;
}

/* Backtracking function to color graph with at most maxColors */
bool graphColoringBacktrack(Graph* graph, int v, int maxColors) {
    /* All vertices colored successfully */
    if (v == graph->N) {
        return true;
    }
    
    /* Try all colors from 1 to maxColors */
    for (int c = 1; c <= maxColors; c++) {
        if (isSafeBacktrack(graph, v, c)) {
            graph->color[v] = c;
            
            /* Recursively color remaining vertices */
            if (graphColoringBacktrack(graph, v + 1, maxColors)) {
                return true;
            }
            
            /* Backtrack */
            graph->color[v] = 0;
        }
    }
    
    return false;
}

/* Find minimum number of colors needed (chromatic number) */
int findChromaticNumberBacktrack(Graph* graph) {
    /* Try increasing number of colors starting from 1 */
    for (int numColors = 1; numColors <= graph->N; numColors++) {
        /* Reset colors */
        for (int i = 0; i < graph->N; i++) {
            graph->color[i] = 0;
        }
        
        if (graphColoringBacktrack(graph, 0, numColors)) {
            return numColors;
        }
    }
    
    return graph->N; /* Worst case: every vertex gets a different color */
}

/* Main function for backtracking approach */
int main() {
    Graph* graph = readGraph();
    
    int chromaticBacktrack = findChromaticNumberBacktrack(graph);
    
    printf("Backtracking: %d\n", chromaticBacktrack);
    
    freeGraph(graph);
    
    return 0;
}
