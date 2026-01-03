#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

//int the old implementation
//even if a vertex has only 2 neighbours i still need to check all the other verices

//linked lists
typedef struct vertex {
    int data; //vertex's index
    struct vertex *next;
} vertex;

typedef struct graph {
    vertex **vertices; //the head of the linked list
    int n;
} graph;

graph *new_graph(int n) {
    graph *my_graph = (graph *)malloc(sizeof(graph));
    my_graph->n = n;
    my_graph->vertices = (vertex**)malloc(n * sizeof(vertex*));
    for (size_t i = 0; i < n; i++) {
        *(my_graph->vertices + i) = NULL;
    }
    return my_graph;
}

void new_edge(graph *actual_graph, int first, int last) {
    vertex* node1 = (vertex*)malloc(sizeof(vertex));
    node1->data = last;
    node1->next = *(actual_graph->vertices + first);
    *(actual_graph->vertices + first) = node1;

    vertex* node2 = (vertex*)malloc(sizeof(vertex));
    node2->data = first;
    node2->next = *(actual_graph->vertices + last);
    *(actual_graph->vertices + last) = node2;
}

void free_memory(graph *actual_graph) {
    for (size_t i = 0; i < actual_graph->n; i++) {
        vertex *aux = *(actual_graph->vertices + i);
        while (aux) {
            vertex *next = aux->next;
            free(aux);
            aux = next;
        }
    }
    free(actual_graph->vertices);
    free(actual_graph);
}

//int check_independent_set(int vertex, int color, graph *actual_graph, int *colors) {
//shadowing, phenomen that happens when both a local and a global variable has the same name
//local variables has priority over global data types
int check_independent_set(int actual_vertex, int color, graph *actual_graph, int *colors) {
    vertex *aux = *(actual_graph->vertices + actual_vertex);
    while (aux != NULL) {
        int neighbor = aux->data;
        // Dacă vecinul are deja culoarea pe care vrem s-o punem -> Conflict
        if (*(colors + neighbor) == color) {
            return 0; 
        }
        aux = aux->next;
    }
    return 1;
}

int saturation_of_vertex(int current_vertex, graph *actual_graph, int *colors) {
    int *colors_nearby_vertices = (int*)calloc(actual_graph->n + 1, sizeof(int));
    if (colors_nearby_vertices == NULL)
        exit(EXIT_FAILURE);
    
    int nr = 0;
    vertex *aux = *(actual_graph->vertices + current_vertex);
    while (aux != NULL) {
        int color = *(colors + aux->data);
        if (color != 0 && *(colors_nearby_vertices + color) == 0) {
            *(colors_nearby_vertices + color) = 1;
         nr++;
        }
        aux = aux->next;
    }
    
    free(colors_nearby_vertices);
    return nr;
}

int degree_vertex(int current_vertex, graph *actual_graph, int *colors) {
    int nr = 0;
    vertex *aux = *(actual_graph->vertices + current_vertex);
    
    while (aux != NULL) {
        int neighbor = aux->data;
        if (*(colors + neighbor) == 0) {
            nr++;
        }
        aux = aux->next;
    }
    return nr;
}

int highest_deg_when_highest_sat(graph *actual_graph, int *colors) {
    int maximum_sat = -1;
    int maximum_degree = -1;
    int the_choosen_one = -1;
    int n = actual_graph->n;

    for (int i = 0; i < n; i++) {
        if (*(colors + i) == 0) {
            int current_sat = saturation_of_vertex(i, actual_graph, colors);
            int current_deg = degree_vertex(i, actual_graph, colors);

            if (current_sat > maximum_sat) {
                maximum_sat = current_sat;
                maximum_degree = current_deg;
             the_choosen_one = i;
            } else if (current_sat == maximum_sat) {
                if (current_deg > maximum_degree) {
                    maximum_degree = current_deg;
                 the_choosen_one = i;
                }
            }
        }
    }
    return the_choosen_one;
}

int smallest_valid_color(int actual_vertex, graph *actual_graph, int *colors) {
    int color = 1;
    while (1) {
        if (check_independent_set(actual_vertex, color, actual_graph, colors)) {
            return color;
        }
        color++;
    }
    return -1; //where are your vertiges????
}

void dsatur(graph *actual_graph, int *colors) {
    int colored_vertices = 0;

    while (colored_vertices < actual_graph->n) {
        int actual_vertex = highest_deg_when_highest_sat(actual_graph, colors);
        
        if (actual_vertex == -1) break;

        int color = smallest_valid_color(actual_vertex, actual_graph, colors);
        *(colors + actual_vertex) = color;
        colored_vertices++;
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    graph *my_graph = new_graph(n);

    for (size_t i = 0; i < m; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        if (x >= 0 && x < n && y >= 0 && y < n) {
            new_edge(my_graph, x, y);
        }
    }

    int *colors = (int *)calloc(n, sizeof(int));

    dsatur(my_graph, colors);

    int max_color = 0;
    for (int i = 0; i < n; i++) {
        if (*(colors + i) > max_color) max_color = *(colors + i);
    }
    printf("%d\n", max_color);

    for (int i = 0; i < n; i++) {
        printf("%d", *(colors + i));
        if (i < n - 1) printf(" ");
    }
    printf("\n");

    free(colors);
    free_memory(my_graph);

    return 0;
}