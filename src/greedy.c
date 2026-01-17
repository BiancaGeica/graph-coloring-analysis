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
    
    /* Initializeaza listele de adiacenta si matricile */
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
    
    /* Actualizeaza matricea de adiacenta */
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

/* Gaseste maximul dintre doi intregi */
int max(int a, int b) {
    return (a > b) ? a : b;
}

/* Gaseste numarul minim de culori folosind colorarea secventiala greedy */
int findChromaticNumberGreedy(Graph* graph) {
    /* Reseteaza culorile */
    for (int i = 0; i < graph->N; i++) {
        graph->color[i] = 0;
    }
    
    int maxColor = 0;
    
    /* Proceseaza nodurile secvential in ordine (0, 1, 2, ..., N-1) */
    /* Aceasta este o abordare greedy clasica: fa alegerea optima local la fiecare pas */
    for (int v = 0; v < graph->N; v++) {
        /* Gaseste cea mai mica culoare nefolosita de nodurile adiacente */
        bool usedColors[MAXN];
        for (int i = 0; i <= graph->N; i++) {
            usedColors[i] = false;
        }
        
        /* Verifica ce culori sunt folosite de vecinii deja colorati */
        AdjListNode* current = graph->array[v].head;
        while (current) {
            int u = current->dest;
            int neighborColor = graph->color[u];
            if (neighborColor != 0) {
                usedColors[neighborColor] = true;
            }
            current = current->next;
        }
        
        /* Asigneaza cea mai mica culoare disponibila (alegerea greedy) */
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

/* Functia principala pentru abordarea greedy */
int main() {
    Graph* graph = readGraph();
    
    int chromaticGreedy = findChromaticNumberGreedy(graph);
    
    printf("Greedy: %d\n", chromaticGreedy);
    
    freeGraph(graph);
    
    return 0;
}
