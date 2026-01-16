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

/* Find maximum of two integers */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Find minimum number of colors using greedy sequential coloring */
int findChromaticNumberGreedy(Graph* graph) {
    /* Reset colors */
    for (int i = 0; i < graph->N; i++) {
        graph->color[i] = 0;
    }
    
    int maxColor = 0;
    
    /* Process vertices sequentially in order (0, 1, 2, ..., N-1) */
    /* This is a classic greedy approach: make locally optimal choice at each step */
    for (int v = 0; v < graph->N; v++) {
        /* Find the smallest color not used by adjacent vertices */
        bool usedColors[MAXN];
        for (int i = 0; i <= graph->N; i++) {
            usedColors[i] = false;
        }
        
        /* Check which colors are used by already-colored neighbors */
        AdjListNode* current = graph->array[v].head;
        while (current) {
            int u = current->dest;
            if (graph->color[u] != 0) {
                usedColors[graph->color[u]] = true;
            }
            current = current->next;
        }
        
        /* Assign the smallest available color (greedy choice) */
        for (int c = 1; c <= graph->N; c++) {
            if (!usedColors[c]) {
                graph->color[v] = c;
                maxColor = max(maxColor, c);
                break;
            }
        }
    }
    
    return maxColor;
}

/* Main function for greedy approach */
int main() {
    Graph* graph = readGraph();
    
    int chromaticGreedy = findChromaticNumberGreedy(graph);
    
    printf("Greedy: %d\n", chromaticGreedy);
    
    freeGraph(graph);
    
    return 0;
}
