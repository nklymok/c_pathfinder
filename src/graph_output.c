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
    printf("Path: %s -> %s\n", graph->islands[island1], graph->islands[island2]);
}

void print_distance(t_graph *graph, int route_weight) {
    (void) graph;
    printf("Distance: %d\n", route_weight);
}

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
}

void output_graph_routes(t_graph *graph) {
    //char **paths = graph->literal_paths;
    int *weights = graph->weights;
    int island_count = graph->island_count;
    int route_weight;

    for (int i = 0; i < island_count; i++) {
        for (int j = i + 1; j < island_count; j++) {
            route_weight = weights[i * island_count + j];
            print_separator();
            print_path(graph, i, j);
//            print_route(graph, island1_weight, island2_weight);
            print_distance(graph, route_weight);
            print_separator();
        }
    }
}
