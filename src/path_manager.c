#include "pathfinder.h"

void set_initial_path(t_graph *graph, int isl1_index, int isl2_index) {
    int lpath1_index = isl1_index * graph->island_count + isl2_index;
    int lpath2_index = isl2_index * graph->island_count + isl1_index;
    char *island1 = graph->islands[isl1_index];
    char *island2 = graph->islands[isl2_index];
    char *temp_str1 = mx_strjoin(island1, " -> ");
    char *temp_str2 = mx_strjoin(temp_str1, island2);

    graph->literal_paths[lpath1_index] = mx_strdup(temp_str2);
    free(temp_str1);
    free(temp_str2);
    temp_str1 = mx_strjoin(island2, " -> ");
    temp_str2 = mx_strjoin(temp_str1, island1);
    graph->literal_paths[lpath2_index] = mx_strdup(temp_str2);
    free(temp_str1);
    free(temp_str2);
}

void set_literal_path(t_graph *graph, int from, int to, int proxy) {
    char **paths = graph->literal_paths;
    int isl_count = graph->island_count;
    char *from_proxy = paths[from * isl_count + proxy];
    char *proxy_to = paths[proxy * isl_count + to];
    char *temp_join = NULL;

    proxy_to = &proxy_to[mx_get_char_index(proxy_to, '>') + 2];
    temp_join = mx_strjoin(from_proxy, " -> ");
    if (paths[from * isl_count + to]) {
        free(paths[from * isl_count + to]);
        paths[from * isl_count + to] = NULL;
    }
    paths[from * isl_count + to] = mx_strjoin(
                                temp_join,
                                proxy_to);
    free(temp_join);
    temp_join = NULL;
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
    int path1;
    int path2;

    // Floyd-Warshall algorithm (j - from, k - to, i - proxy)
    for (int i = 0; i < isl_count; i++) {
        for (int j = 0; j < isl_count; j++) {
            if (j == i) continue;
            path1 = graph->weights[j * isl_count + i];
            for (int k = 0; k < isl_count; k++) {
                if (j == k || j == i) continue;
                curr_path = &graph->weights[j * isl_count + k];
                path2 = graph->weights[i * isl_count + k];
                if (path1 != -1 && path2 != -1 &&
                    (*curr_path > path1 + path2 || *curr_path == -1)) {
                    *curr_path = path1 + path2;
                    set_literal_path(graph, j, k, i);
                }
            }
        }
    }
}
