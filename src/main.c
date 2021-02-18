#include "pathfinder.h"

void del_graph(t_graph **p_graph) {
    t_graph *graph = *p_graph;
    free(graph->weights);
    mx_del_strarr(&graph->islands);
    free(graph);
}

void output_graph(t_graph *graph) {
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

// check parameter count -> check if file exists / empty
// parse map -> check for exceptions -> if so / report & exit
// print out solution
int main(int argc, char **argv) {
    t_graph *graph = malloc(sizeof(t_graph));
    if (!handle_errors(argc, argv, graph)) {
        exit(0);
    }
    output_graph(graph);
    del_graph(&graph);
}
