#include <stdio.h>
#include <stdlib.h>

/* Structura pentru a stoca informatii despre un nod
 * indexul original al nodului (0, 1, ... N-1)
 * gradul nodului (numarul de muchii)
 * culoarea atribuita (-1 daca nu este colorat)
 */
typedef struct {
    int id;
    int degree;
    int color;
} Node;

/* Functie de comparare folosita de qsort pentru a sorta in ordine descrescatoare a gradului */
int compareNodes(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    /* Ordine descrescatoare */
    return (nodeB->degree - nodeA->degree);
}

int main() {
    int N, M;
    int u, v;

   /* 1. Citire date de intrare
    * N = numarul de noduri, M = numarul de muchii
    */
    if (scanf("%d %d", &N, &M) != 2) 
        return 1;

    /* Alocare dinamica pentru matricea de adiacenta
     * Aloca un vector de pointeri (randurile matricei) 
     */
    char **adjMatrix = (char **)malloc(N * sizeof(char *));
    
    /* Aloca fiecare rand individual */
    for (int i = 0; i < N; i++) {
        /* Folosind calloc pentru a initializa cu 0 */
        adjMatrix[i] = (char *)calloc(N, sizeof(char));
    }

    /* Initializare noduri */
    Node *nodes = (Node *)malloc(N * sizeof(Node));
    for (int i = 0; i < N; i++) {
        nodes[i].id = i;
        nodes[i].degree = 0;
        /* -1 = necolorat */
        nodes[i].color = -1;
    }

    /* Citeste muchiile, construieste matricea de adiacenta si calculeaza gradele */
    for (int i = 0; i < M; i++) {
        /* Valideaza operatia de I/O: asigura-te ca exact 2 intregi au fost cititi cu succes. 
         * Daca inputul este malformat sau se ajunge la EOF neasteptat, opreste procesarea pentru 
         * a evita comportamentul nedefinit.
         * Cu alte cuvinte - am rezolvat un warning.
         */
        if (scanf("%d %d", &u, &v) != 2)
            break;
        if(u < N && v < N) {
            /* Marcheaza muchia in matricea dinamica */
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
            /* Incrementeaza gradele */
            nodes[u].degree++;
            nodes[v].degree++;
        }
    }

    /* 2. Sorteaza nodurile descrescator dupa grad (specific Welsh-Powell) 
     * Sortez vectorul de structuri, dar pastrez 'id' inauntru pentru a accesa 
     * corect matricea mai tarziu.
     */
    qsort(nodes, N, sizeof(Node), compareNodes);

    /* 3. Executia algoritmului */
    int colorCount = 0;
    int coloredNodes = 0;

    /* Incepe o noua culoare (1, 2, 3...) */
    while (coloredNodes < N) {
        colorCount++;
        
        /* Gaseste primul nod necolorat in lista sortata pentru a incepe aceasta noua culoare */
        for (int i = 0; i < N; i++) {
            if (nodes[i].color == -1) {
                /* Atribuie culoarea curenta acestui nod */
                nodes[i].color = colorCount;
                coloredNodes++;

                /* Acum incerc sa atribui aceeasi culoare altor noduri necolorate din lista,
                 * doar daca nu sunt adiacente cu niciun nod care are deja aceasta culoare.
                 */
                for (int j = i + 1; j < N; j++) {
                    if (nodes[j].color == -1) {
                        int canColor = 1;
                        
                        /* Verifica daca nodes[j] este in conflict cu nodes[i] sau orice alt nod 
                         * care a primit 'colorCount' in aceasta iteratie.
                         * Trebuie sa verific conflictele cu toate nodurile care au primit deja 
                         * culoarea curenta.
                         */

                        for (int k = 0; k < N; k++) {
                            if (nodes[k].color == colorCount) {
                                /* Verifica adiacenta folosind ID-urile originale */
                                if (adjMatrix[nodes[j].id][nodes[k].id] == 1) {
                                    /* Conflict gasit */
                                    canColor = 0;
                                    break;
                                }
                            }
                        }

                        /* Daca nu e conflict, atribuie culoarea */
                        if (canColor) {
                            nodes[j].color = colorCount;
                            coloredNodes++;
                        }
                    }
                }
                /* Am terminat o trecere pentru culoarea curenta */
                break;
            }
        }
    }

    /* Afisare rezultat */
    printf("%d\n", colorCount);
    
    /* Afiseaza culorile in ordinea originala a nodurilor (0, 1, 2...), 
     * nu in ordinea sortata.
     * Folosind un vector auxiliar pentru afisarea finala.
     */
    int *finalColors = (int *)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) {
        finalColors[nodes[i].id] = nodes[i].color;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", finalColors[i]);
    }
    printf("\n");

    /* Curatare memorie
     * Elibereaza memoria alocata dinamic
     */
    free(nodes);
    free(finalColors);

    /* Elibereaza matricea de adiacenta (fiecare rand, apoi vectorul de pointeri) */
    for (int i = 0; i < N; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);

    return 0;
}
