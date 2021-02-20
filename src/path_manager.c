#include "pathfinder.h"

void set_litaral_path(t_graph *graph, int island1, int island2) {
    (void) graph;
    (void) island1;
    (void) island2;
}

void find_paths(t_graph *graph) {
    int isl_count = graph->island_count;
    int *curr_path;
    int path1 = 0;
    int path2 = 0;
    // Floyd-Warshall algorithm
    for (int i = 0; i < isl_count; i++) {
        for (int j = 0; j < isl_count; j++) {
            path1 = graph->weights[j * isl_count + i];
            for (int k = 0; k < isl_count; k++) {
                curr_path = &graph->weights[j * isl_count + k];
                path2 = graph->weights[i * isl_count + k];
                if (path1 != -1 && path2 != -1 &&
                    (*curr_path > path1 + path2 || *curr_path == -1)) {
                    *curr_path = path1 + path2;
                }
            }
        }
    }
}
