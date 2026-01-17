#include "graph_coloring.h"

/* Functie pentru a crea un nou nod in lista de adiacenta */
AdjListNode* createNode(int dest) {
    AdjListNode* newNode = (AdjListNode*)malloc(sizeof(AdjListNode));
    newNode->dest = dest;
    newNode->next = NULL;
    return newNode;
}

/* Functie pentru a crea un graf cu N noduri */
Graph* createGraph(int N, int M) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->N = N;
    graph->M = M;
    graph->array = (AdjList*)malloc(N * sizeof(AdjList));
    
    /* Initializare liste de adiacenta si matrici */
    for (int i = 0; i < N; i++) {
        graph->array[i].head = NULL;
        graph->color[i] = 0;
        for (int j = 0; j < N; j++) {
            graph->adjMatrix[i][j] = false;
        }
    }
    
    return graph;
}

/* Functie pentru a adauga o muchie intr-un graf neorientat */
void addEdge(Graph* graph, int u, int v) {
    /* Adauga muchie de la u la v */
    AdjListNode* newNode = createNode(v);
    newNode->next = graph->array[u].head;
    graph->array[u].head = newNode;
    
    /* Adauga muchie de la v la u (neorientat) */
    newNode = createNode(u);
    newNode->next = graph->array[v].head;
    graph->array[v].head = newNode;
    
    /* Actualizare matrice de adiacenta */
    graph->adjMatrix[u][v] = true;
    graph->adjMatrix[v][u] = true;
}

/* Functie pentru a elibera memoria grafului */
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

/* Functie pentru a citi graful de la intrare */
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

/* Verifica daca asignarea curenta a culorii este sigura pentru nodul v */
bool isSafeBacktrack(Graph* graph, int v, int c) {
    AdjListNode* current = graph->array[v].head;
    
    /* Verifica toate nodurile adiacente */
    while (current) {
        int u = current->dest;
        if (graph->color[u] == c) {
            return false;
        }
        current = current->next;
    }
    
    return true;
}

/* Functie de backtracking pentru a colora graful cu cel mult maxColors */
bool graphColoringBacktrack(Graph* graph, int v, int maxColors) {
    /* Toate nodurile au fost colorate cu succes */
    if (v == graph->N) {
        return true;
    }
    
    /* Incearca toate culorile de la 1 la maxColors */
    for (int c = 1; c <= maxColors; c++) {
        if (isSafeBacktrack(graph, v, c)) {
            graph->color[v] = c;
            
            /* Coloreaza recursiv nodurile ramase */
            if (graphColoringBacktrack(graph, v + 1, maxColors)) {
                return true;
            }
            
            /* Revenire (Backtrack) */
            graph->color[v] = 0;
        }
    }
    
    return false;
}

/* Gaseste numarul minim de culori necesare (numarul cromatic) */
int findChromaticNumberBacktrack(Graph* graph) {
    /* Incearca cresterea numarului de culori incepand de la 1 */
    for (int numColors = 1; numColors <= graph->N; numColors++) {
        /* Reseteaza culorile */
        for (int i = 0; i < graph->N; i++) {
            graph->color[i] = 0;
        }
        
        if (graphColoringBacktrack(graph, 0, numColors)) {
            return numColors;
        }
    }
    
    return graph->N; /* Cel mai rau caz: fiecare nod primeste o culoare diferita */
}

/* Functia principala pentru abordarea backtracking */
int main() {
    Graph* graph = readGraph();
    
    int chromaticBacktrack = findChromaticNumberBacktrack(graph);
    
    printf("Backtracking: %d\n", chromaticBacktrack);
    
    freeGraph(graph);
    
    return 0;
}