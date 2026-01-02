#include <stdio.h>
#include <stdlib.h>

/* Structure to store information about a node
 * original node index (0, 1, ... N-1)
 * node degree (number of edges)
 * assigned color (-1 if it's not colored)
 */
typedef struct {
    int id;
    int degree;
    int color;
} Node;

/* Comparator function used by qsort to sort in descending order of degree */
int compareNodes(const void *a, const void *b) {
    Node *nodeA = (Node *)a;
    Node *nodeB = (Node *)b;
    /* Descending order */
    return (nodeB->degree - nodeA->degree);
}

int main() {
    int N, M;
    int u, v;

   /* 1. Read input data
    * N = number of nodes, M = number of edges
    */
    if (scanf("%d %d", &N, &M) != 2) 
        return 1;

    /* Dynamic allocation for adjacency matrix
     * Allocate an array of pointers (the rows of the matrix) 
     */
    char **adjMatrix = (char **)malloc(N * sizeof(char *));
    
    /* Allocate each row individually */
    for (int i = 0; i < N; i++) {
        /* Using calloc to initialize with 0 */
        adjMatrix[i] = (char *)calloc(N, sizeof(char));
    }

    /* Initialize nodes */
    Node *nodes = (Node *)malloc(N * sizeof(Node));
    for (int i = 0; i < N; i++) {
        nodes[i].id = i;
        nodes[i].degree = 0;
        /* -1 = uncolored */
        nodes[i].color = -1;
    }

    /* Read edges, build adjacency matrix, and calculate degrees */
    for (int i = 0; i < M; i++) {
        /* Validate the I/O operation: ensure exactly 2 integers were successfully read. 
         * If input is malformed or EOF is reached unexpectedly, stop processing to 
         * avoid undefined behavior.
         * In other words - I solved a warning.
         */
        if (scanf("%d %d", &u, &v) != 2)
            break;
        if(u < N && v < N) {
            /* Mark the edge in the dynamic matrix */
            adjMatrix[u][v] = 1;
            adjMatrix[v][u] = 1;
            /* Increment degrees */
            nodes[u].degree++;
            nodes[v].degree++;
        }
    }

    /* 2. Sort nodes in descending order by degree (specific to Welsh-Powell) 
     * I sort the array of structures, but I keep 'id' inside to access the 
     * matrix correctly later.
     */
    qsort(nodes, N, sizeof(Node), compareNodes);

    /* 3. Algorithm execution */
    int colorCount = 0;
    int coloredNodes = 0;

    /* Start a new color (1, 2, 3...) */
    while (coloredNodes < N) {
        colorCount++;
        
        /* Find the first uncolored node in the sorted list to start this new color */
        for (int i = 0; i < N; i++) {
            if (nodes[i].color == -1) {
                /* Assign the current color to this node */
                nodes[i].color = colorCount;
                coloredNodes++;

                /* Now I try to assign the same color to other uncolored nodes in the list,
                 * only if they are not adjacent to any node that already has this color.
                 */
                for (int j = i + 1; j < N; j++) {
                    if (nodes[j].color == -1) {
                        int canColor = 1;
                        
                        /* Check if nodes[j] conflicts with nodes[i] or any other node 
                         * that has been assigned 'colorCount' in this iteration.
                         * I must check for conflicts with all nodes that have already 
                         * received the current color
                         */

                        for (int k = 0; k < N; k++) {
                            if (nodes[k].color == colorCount) {
                                /* Check adjacency using the original IDs */
                                if (adjMatrix[nodes[j].id][nodes[k].id] == 1) {
                                    /* Conflict found */
                                    canColor = 0;
                                    break;
                                }
                            }
                        }

                        /* If no conflict, assign the color */
                        if (canColor) {
                            nodes[j].color = colorCount;
                            coloredNodes++;
                        }
                    }
                }
                /* Finished one pass for the current color */
                break;
            }
        }
    }

    /* Output result */
    printf("%d\n", colorCount);
    
    /* Print colors in the original order of nodes (0, 1, 2...), 
     * not the sorted order.
     * Using an auxiliary array for the final output.
     */
    int *finalColors = (int *)malloc(N * sizeof(int));
    for(int i = 0; i < N; i++) {
        finalColors[nodes[i].id] = nodes[i].color;
    }

    for (int i = 0; i < N; i++) {
        printf("%d ", finalColors[i]);
    }
    printf("\n");

    /* Memory cleanup
     * Free the dynamically allocated memory
     */
    free(nodes);
    free(finalColors);

    /* Free the adjacency matrix (each row, then the array of pointers) */
    for (int i = 0; i < N; i++) {
        free(adjMatrix[i]);
    }
    free(adjMatrix);

    return 0;
}
