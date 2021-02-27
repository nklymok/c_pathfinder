/*
 * graph_output provides main functions to output the graph:
 *
 * - output_graph_matrix(t_graph graph) - prints graph as a matrix
 * - output_graph_routes(t_graph graph) - prints graph in a way,
 *      that is described in ucode pdf.
 *
 * other fucntions are complementary to these two,
 *      and are used only internally.
 */

#include "pathfinder.h"

void print_separator() {
    for (int i = 0; i < 40; i++) {
        mx_printchar('=');
    }
    mx_printchar('\n');
}

void print_path(t_graph *graph, int island1, int island2) {
    mx_printstr("Path: ");
    mx_printstr(graph->islands[island1]);
    mx_printstr(" -> ");
    mx_printstr(graph->islands[island2]);
    mx_printchar('\n');
}

void print_distance(t_graph *graph, int island1, int island2) {
    int isl_count = graph->island_count;

    mx_printstr("Distance: ");
    mx_printstr(graph->literal_distances[island1 * isl_count + island2]);
    mx_printchar('\n');
}

void print_route(t_graph *graph, int island1, int island2) {
    int isl_count = graph->island_count;

    mx_printstr("Route: ");
    mx_printstr(graph->literal_paths[island1 * isl_count + island2]);
    mx_printchar('\n');
}

/*
 * For debugging purposes
void output_graph_matrix(t_graph *graph) {
    char **islands = graph->islands;
    int *weights = graph->weights;
    printf("\t");
    for (int i = 0; islands[i]; i++) {
        printf("%s\t", islands[i]);
    }
    printf("\n");
    for (int i = 0; i < graph->island_count; i++) {
        printf("%s\t", islands[i]);
        for (int j = 0; j < graph->island_count; j++) {
            printf("%d\t", weights[i * graph->island_count + j]);
        }
        printf("\n");
    }
}*/

void output_graph_routes(t_graph *graph) {
    int island_count = graph->island_count;

    for (int i = 0; i < island_count; i++) {
        for (int j = i + 1; j < island_count; j++) {
            print_separator();
            print_path(graph, i, j);
            print_route(graph, i, j);
            print_distance(graph, i, j);
            print_separator();
        }
    }
}
