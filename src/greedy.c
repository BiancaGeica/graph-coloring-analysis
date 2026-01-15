#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/**
 * Structure for Adjacency Lists (efficient for large/sparse graphs)
 */
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjLists;
} Graph;

// Function to create a new node
Node* createNode(int v) {
    Node* newNode = malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

// Function to create the graph
Graph* createGraph(int vertices) {
    Graph* graph = malloc(sizeof(Graph));
    graph->numVertices = vertices;
    graph->adjLists = malloc(vertices * sizeof(Node*));
    for (int i = 0; i < vertices; i++)
        graph->adjLists[i] = NULL;
    return graph;
}

// Function to add an edge (undirected graph)
void addEdge(Graph* graph, int s, int d) {
    Node* newNode = createNode(d);
    newNode->next = graph->adjLists[s];
    graph->adjLists[s] = newNode;

    newNode = createNode(s);
    newNode->next = graph->adjLists[d];
    graph->adjLists[d] = newNode;
}

/**
 * Greedy Algorithm for Coloring
 */
void greedyColoring(Graph* graph) {
    int n = graph->numVertices;
    int* result = malloc(n * sizeof(int));
    bool* available = malloc(n * sizeof(bool));

    // Initialization: no node has a color, all colors are available
    for (int i = 0; i < n; i++) {
        result[i] = -1;
        available[i] = true;
    }

    // Assign the first color to the first node
    result[0] = 0;

    for (int u = 1; u < n; u++) {
        // Mark colors of already colored neighbors as unavailable
        Node* temp = graph->adjLists[u];
        while (temp) {
            if (result[temp->vertex] != -1) {
                available[result[temp->vertex]] = false;
            }
            temp = temp->next;
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < n; cr++) {
            if (available[cr]) break;
        }

        result[u] = cr; // Assign color

        // Reset the availability array for the next node
        temp = graph->adjLists[u];
        while (temp) {
            if (result[temp->vertex] != -1) {
                available[result[temp->vertex]] = true;
            }
            temp = temp->next;
        }
    }

    // Calculate K (maximum number of colors used)
    int k = 0;
    for (int i = 0; i < n; i++) {
        if (result[i] > k) k = result[i];
    }

    // Print according to the required format
    printf("%d\n", k + 1);
    for (int i = 0; i < n; i++) {
        printf("%d%s", result[i], (i == n - 1) ? "" : " ");
    }
    printf("\n");

    free(result);
    free(available);
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    Graph* graph = createGraph(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(graph, u, v);
    }

    greedyColoring(graph);

    return 0;
}