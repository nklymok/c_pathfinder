#include "pathfinder.h"

void del_graph(t_graph **p_graph) {
    t_graph *graph = *p_graph;
    free(graph->weights);
    mx_del_strarr(&graph->islands);
    mx_del_strarr(&graph->literal_paths);
    free(graph);
}

// check parameter count -> check if file exists / empty
// parse map -> check for exceptions -> if so / report & exit
// print out solution
int main(int argc, char **argv) {
    t_graph *graph = malloc(sizeof(t_graph));
    if (!handle_errors(argc, argv, graph)) {
        exit(0);
    }
//    output_graph_matrix(graph);
//    printf("\n\n\n");
    find_paths(graph);
//    output_graph_matrix(graph);
//    printf("\n\n\n");
    output_graph_routes(graph);
    del_graph(&graph);
}
