#include "pathfinder.h"

/*
 * This is a god-blessing fix from an insight I got.
 * The reason behind it is the way I store paths.
 * Instead of using normal 2d arrays,
 * Like I would do in any normal time,
 * I used 1d array with multiplication. Because I couldn't manage 3d char arrs
 * Now, this short piece of code is a savior from memory leaks. Thank you, me.
 */
void del_paths(t_graph *graph) {
    for (int i = 0; i < graph->island_count; i++) {
        for (int j = 0; j < graph->island_count; j++) {
            if (graph->weights[i * graph->island_count + j] > 0 &&
            graph->literal_paths[i * graph->island_count + j]) {
                mx_strdel(&graph->literal_paths[i * graph->island_count + j]);
                graph->literal_paths[i * graph->island_count + j] = NULL;
            }
        }
    }
    free(*graph->literal_paths);
    free(graph->literal_paths);
}

void del_distances(t_graph *graph) {
    for (int i = 0; i < graph->island_count; i++) {
        for (int j = 0; j < graph->island_count; j++) {
            if (graph->weights[i * graph->island_count + j] > 0 &&
                graph->literal_distances[i * graph->island_count + j]) {
                mx_strdel(&graph->literal_distances[i * graph->island_count + j]);
                graph->literal_distances[i * graph->island_count + j] = NULL;
            }
        }
    }
    free(*graph->literal_distances);
    free(graph->literal_distances);
}

void del_graph(t_graph **p_graph) {
    t_graph *graph = *p_graph;
    del_paths(graph);
    del_distances(graph);
    free(graph->weights);
    mx_del_strarr(&graph->islands);
    free(graph);
}

int main(int argc, char **argv) {
    t_graph *graph = malloc(sizeof(t_graph));
    if (!handle_errors(argc, argv, graph)) {
        free(graph);
        exit(0);
    }
    find_paths(graph);
    output_graph_routes(graph);
    del_graph(&graph);
}
