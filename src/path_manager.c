#include "pathfinder.h"

char *name_by_index(t_graph *graph, int index) {
    return graph->islands[index];
}

void set_literal_path(t_graph *graph, int from, int to, int proxy) {
    char **paths = graph->literal_paths;
    int isl_count = graph->island_count;
    char *from_proxy = paths[from * isl_count + proxy];
    char *proxy_to = paths[proxy * isl_count + to];
    char *to_proxy = paths[to * isl_count + proxy];
    char *proxy_from = paths[proxy * isl_count + from];
    char *temp_join = NULL;

    proxy_to = &proxy_to[mx_get_char_index(proxy_to, '>') + 2];
    proxy_from = &proxy_from[mx_get_char_index(proxy_from, '>') + 2];
    temp_join = mx_strjoin(from_proxy, " -> ");
    if (paths[from * isl_count + to]) {
        free(paths[from * isl_count + to]);
    }
    paths[from * isl_count + to] = mx_strjoin(
                                temp_join,
                                proxy_to);
    free(temp_join);
    temp_join = mx_strjoin(to_proxy, " -> ");
    if (paths[to * isl_count + from]) {
        free(paths[to * isl_count + from]);
    }
    paths[to * isl_count + from] = mx_strjoin(
                                    mx_strjoin(to_proxy, " -> "),
                                    proxy_from);
    free(temp_join);
}

/*
 * weight_index (w_i) = isl1_index * total_islands + isl2_index
 * Hence, to get isl1_index, { (w_i - isl2_index) / total } may be used.
 * Same with isl2_index.
 * Using isl1_index & isl2_index, their names could be got via islands array.
 */
void find_paths(t_graph *graph) {
    int isl_count = graph->island_count;
    int *curr_path;
    int *curr_path_inv;
    int path1 = 0;
    int path2 = 0;

    // Floyd-Warshall algorithm (j - from, k - to, i - proxy)
    for (int i = 0; i < isl_count; i++) {
        for (int j = 0; j < isl_count; j++) {
            if (j == i) continue;
            path1 = graph->weights[j * isl_count + i];
            for (int k = 0; k < isl_count; k++) {
                if (j == k || j == i) continue;
                curr_path = &graph->weights[j * isl_count + k];
                curr_path_inv = &graph->weights[k * isl_count + j];
                path2 = graph->weights[i * isl_count + k];
                if (path1 != -1 && path2 != -1 &&
                    (*curr_path > path1 + path2 || *curr_path == -1)) {
                    *curr_path = path1 + path2;
                    *curr_path_inv = path1 + path2;
                    set_literal_path(graph, j, k, i);
                    set_literal_path(graph, k, j, i);
                }
            }
        }
    }
}
