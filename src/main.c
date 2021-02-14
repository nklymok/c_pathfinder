#include "pathfinder.h"

// check parameter count -> check if file exists / empty
// parse map -> check for exceptions -> if so / report & exit
// print out solution
int main(int argc, char **argv) {
    t_graph *graph = malloc(sizeof(t_graph));
    if (!handle_errors(argc, argv, graph)) {
        exit(0);
    }
}

