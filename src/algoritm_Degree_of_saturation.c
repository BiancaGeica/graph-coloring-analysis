#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//DSatur = degree of saturation
//Saturation = number of distinct colors used by it's neighbours
//if all the neighbours of a vertex has the same color the saturation is 1
//if i have 5 neighbours with 3 different colors the current_sat is 3

//matrix of adjacency
uint8_t** memory_alloc_matrix(int n) {
    uint8_t **matrix = (uint8_t**)malloc(n * sizeof(uint8_t*));
    if (matrix == NULL) {
        exit(EXIT_FAILURE);
    } 

    for (size_t i = 0; i < n; i++) {
        *(matrix + i) = (uint8_t*)calloc(n, sizeof(uint8_t));
        if (*(matrix + i) == NULL)
            exit(EXIT_FAILURE);
    }
    return matrix;
}

void free_memory(uint8_t **matrix, int n) {
    for (size_t i = 0; i < n; i++)
        free(*(matrix + i));
    free(matrix);
}

uint8_t* memory_alloc_vector(int n) {
    uint8_t *vector = (uint8_t *)calloc(n, sizeof(uint8_t));
    if (vector == NULL)
        exit(EXIT_FAILURE);

    return vector;
}

//independent set = group of vertexes that doesn't have edges between the same color
int check_independent_set(int vertex, int color, int n, uint8_t **matrix, uint8_t *colors) {
    for (size_t i = 0; i < n; i++) {
        if (*(*(matrix + vertex) + i) == 1) {
            if (*(colors + i) == color)
                return 0;
        }
    }

    return 1;
}

int saturation_of_vertex(int vertex, int n, uint8_t **matrix, uint8_t *colors) {
    uint8_t *colors_nearby_vertices = (uint8_t*)calloc(n + 1, sizeof(uint8_t));
    if (colors_nearby_vertices == NULL)
        exit(EXIT_FAILURE);
    
    int nr = 0;
    for (size_t i = 0; i < n; i++) {
        if (*(*(matrix + vertex) + i) == 1 && *(colors + i) != 0) {
            if (*(colors_nearby_vertices + *(colors + i)) == 0) {
                *(colors_nearby_vertices + *(colors + i)) = 1;
                nr++;
            }
        }
    }

    free(colors_nearby_vertices);
    return nr;
}

int degree_vertex(int vertex, int n, uint8_t **matrix, uint8_t *colors) {
    int nr = 0;
    for (size_t i = 0; i < n; i++) {
        // Count uncolored neighbours
        if (*(*(matrix + vertex) + i) == 1 && *(colors + i) == 0)
            nr++;
    }
    return nr;
}

int highest_deg_when_highest_sat(int n, uint8_t **matrix, uint8_t *colors) {
    int maximum_sat = -1;
    int maximum_degree = -1;
    int vertex = -1;
    
    for (int i = 0; i < n; i++) {
        if (*(colors + i) == 0) {
            int current_sat = saturation_of_vertex(i, n, matrix, colors);
            int current_degree = degree_vertex(i, n, matrix, colors);
            
            // DSATUR logic: when all the verices has the same saturation, we search their highest degree
            if (current_sat > maximum_sat || (current_sat == maximum_sat && current_degree > maximum_degree)) {
                maximum_sat = current_sat;
                maximum_degree = current_degree;
                vertex = i;
            }
        }
    }
    
    return vertex;
}

int smallest_valid_color(int vertex, int n, uint8_t **matrix, uint8_t *colors) {
    int max_color = 0;
    for (int i = 0; i < n; i++) {
        if (*(colors + i) > max_color) {
            max_color = *(colors + i);
        }
    }
    
    for (int j = 1; j <= max_color + 1; j++) { 
        if (check_independent_set(vertex, j, n, matrix, colors)) {
            return j;
        }
    }
    
    //if i don't have enough colors I add one more
    return max_color + 1;
}

void dsatur(int n, uint8_t **matrix, uint8_t *colors) {
    int colored_vertices = 0;
    
    while (colored_vertices < n) {
        int vertex = highest_deg_when_highest_sat(n, matrix, colors);
        
        if (vertex == -1)
            break;
        
        int color = smallest_valid_color(vertex, n, matrix, colors);
        *(colors + vertex) = color;
        
        colored_vertices++;
    }
}

int main() {
    int n, m;
    
    if(scanf("%d %d", &n, &m) != 2) return 0; //n-verices m-edges
    
    uint8_t **matrix = memory_alloc_matrix(n);
    
    for (int i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        
        if (x >= 0 && x < n && y >= 0 && y < n) {
            *(*(matrix + x) + y) = 1;
            *(*(matrix + y) + x) = 1;
        }
    }
    
    uint8_t *colors = memory_alloc_vector(n);
    
    dsatur(n, matrix, colors);
    
    int max_color = 0;
    for (int i = 0; i < n; i++) {
        if (*(colors + i) > max_color) {
            max_color = *(colors + i);
        }
    }
    printf("%d\n", max_color);
    
    for (int i = 0; i < n; i++) {
        printf("%d", *(colors + i));
        if (i < n - 1) {
            printf(" ");
        }
    }
    printf("\n");
    
    free(colors);
    free_memory(matrix, n);
    
    return 0;
}