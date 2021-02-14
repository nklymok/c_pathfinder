#include "pathfinder.h"

void del_graph(t_graph **graph) {
    free(*graph);
}

// check parameter count -> check if file exists / empty
// parse map -> check for exceptions -> if so / report & exit
// print out solution
int main(int argc, char **argv) {
    t_graph *graph = malloc(sizeof(t_graph));
    if (!handle_errors(argc, argv, graph)) {
        del_graph(&graph);
        exit(0);
    }
    del_graph(&graph);
}
