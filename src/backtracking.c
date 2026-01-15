#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Check if it is safe to color node 'v' with color 'c'
bool isSafe(int v, int n, int graph[n][n], int color[], int c) {
    for (int i = 0; i < n; i++) {
        if (graph[v][i] && c == color[i]) {
            return false;
        }
    }
    return true;
}

// Recursive function to try coloring with 'm' colors
bool graphColoringUtil(int n, int graph[n][n], int m, int color[], int v) {
    // If all nodes are colored, return true
    if (v == n) {
        return true;
    }

    // Try different colors from 0 to m-1
    for (int c = 0; c < m; c++) {
        if (isSafe(v, n, graph, color, c)) {
            color[v] = c;

            // Recur for the rest of the nodes
            if (graphColoringUtil(n, graph, m, color, v + 1)) {
                return true;
            }

            // If assigning color 'c' doesn't lead to a solution, remove it (backtrack)
            color[v] = -1;
        }
    }

    return false;
}

void solveBacktracking(int n, int graph[n][n]) {
    int* color = malloc(n * sizeof(int));
    int k;

    // Successively try to color the graph with 1, 2, 3... colors
    // until we find the minimum number (K) that allows a valid coloring.
    for (k = 1; k <= n; k++) {
        for (int i = 0; i < n; i++) color[i] = -1;

        if (graphColoringUtil(n, graph, k, color, 0)) {
            break; // Found the smallest K
        }
    }

    // Print according to the required format
    printf("%d\n", k);
    for (int i = 0; i < n; i++) {
        printf("%d%s", color[i], (i == n - 1) ? "" : " ");
    }
    printf("\n");

    free(color);
}

int main() {
    int n, m;
    if (scanf("%d %d", &n, &m) != 2) return 0;

    // Use adjacency matrix for backtracking (few nodes)
    int (*graph)[n] = calloc(n, sizeof *graph);

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        graph[u][v] = 1;
        graph[v][u] = 1;
    }

    solveBacktracking(n, graph);

    free(graph);
    return 0;
}