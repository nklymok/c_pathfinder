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

void print_complex_route(t_graph *graph, int island1, int island2) {
    print_separator();
    print_path(graph, island1, island2);
    print_route(graph, island1, island2);
    print_distance(graph, island1, island2);
    print_separator();
}

void print_alternatives(t_graph *graph, int island1, int island2) {
    int isl_count = graph->island_count;
    int shortest_path = graph->weights[island1 * isl_count + island2];
    char *literal_path = graph->literal_paths[island1 * isl_count + island2];
    char *lpath1 = NULL;
    char *lpath2 = NULL;
    char *ldist1 = NULL;
    char *ldist2 = NULL;
    char *alt_path = NULL;
    char *alt_dist = NULL;
    int path1;
    int path2;
    // TODO print one-bridge alternatives (in case FIFO two-bridge solution is first)
    for (int proxy = 0; proxy < isl_count; proxy++) {
        if (proxy == island2 || proxy == island1) continue;
        path1 = graph->weights[island1 * isl_count + proxy];
        path2 = graph->weights[proxy * isl_count + island2];
        if (path1 != -1 && path2 != -1 &&
            (shortest_path == path1 + path2 || shortest_path == -1)) {
            lpath1 = graph->literal_paths[island1 * isl_count + proxy];
            lpath2 = graph->literal_paths[proxy * isl_count + island2];
            alt_path = build_literal_path(lpath1, lpath2);
            if (mx_strcmp(alt_path, literal_path) == 0) {
                mx_strdel(&alt_path);
                alt_path = NULL;
                continue;
            }
            ldist1 = graph->literal_distances[island1 * isl_count + proxy];
            ldist2 = graph->literal_distances[proxy * isl_count + island2];
            alt_dist = build_literal_distance(ldist1, ldist2, shortest_path);
            print_separator();
            print_path(graph, island1, island2);
            mx_printstr("Route: ");
            mx_printstr(alt_path);
            mx_printchar('\n');
            mx_printstr("Distance: ");
            mx_printstr(alt_dist);
            mx_printchar('\n');
            // todo distance too
            print_separator();
            mx_strdel(&alt_path);
            mx_strdel(&alt_dist);
        }
    }
}

void output_graph_routes(t_graph *graph) {
    int island_count = graph->island_count;

    for (int i = 0; i < island_count; i++) {
        for (int j = i + 1; j < island_count; j++) {
            print_complex_route(graph, i, j);
            print_alternatives(graph, i, j);
        }
    }
}
