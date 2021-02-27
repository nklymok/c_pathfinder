#include "pathfinder.h"

void set_initial_path(t_graph *graph, int isl1_index, int isl2_index) {
    int lpath1_index = isl1_index * graph->island_count + isl2_index;
    int lpath2_index = isl2_index * graph->island_count + isl1_index;
    char *island1 = graph->islands[isl1_index];
    char *island2 = graph->islands[isl2_index];
    char *temp_str1;
    char *temp_str2;
    // Direct way
    temp_str1 = mx_strjoin(island1, " -> ");
    temp_str2 = mx_strjoin(temp_str1, island2);
    graph->literal_paths[lpath1_index] = mx_strdup(temp_str2);
    free(temp_str1);
    free(temp_str2);
    // Reversed way
    temp_str1 = mx_strjoin(island2, " -> ");
    temp_str2 = mx_strjoin(temp_str1, island1);
    graph->literal_paths[lpath2_index] = mx_strdup(temp_str2);
    free(temp_str1);
    free(temp_str2);
}

void set_initial_distance(t_graph *graph, int isl1_index, int isl2_index) {
    int isl_count = graph->island_count;
    int ldist1_index = isl1_index * isl_count + isl2_index;
    int ldist2_index = isl2_index * isl_count + isl1_index;
    int weigth_l1_l2 = graph->weights[isl1_index * isl_count + isl2_index];
    char *dist = mx_itoa(weigth_l1_l2);

    graph->literal_distances[ldist1_index] = mx_strdup(dist);
    graph->literal_distances[ldist2_index] = mx_strdup(dist);
    mx_strdel(&dist);
}

char *build_literal_path(char *from_proxy, char *proxy_to) {
    char *result = NULL;
    char *temp_join = NULL;

    proxy_to = &proxy_to[mx_get_char_index(proxy_to, '>') + 2];
    temp_join = mx_strjoin(from_proxy, " -> ");
    result = mx_strjoin(temp_join, proxy_to);
    free(temp_join);
    return result;
}

void set_literal_path(t_graph *graph, int from, int to, int proxy) {
    char **paths = graph->literal_paths;
    int isl_count = graph->island_count;
    char *from_proxy = paths[from * isl_count + proxy];
    char *proxy_to = paths[proxy * isl_count + to];

    if (paths[from * isl_count + to]) {
        free(paths[from * isl_count + to]);
        paths[from * isl_count + to] = NULL;
    }
    paths[from * isl_count + to] = build_literal_path(from_proxy, proxy_to);
}

char *build_literal_distance(char *from_proxy_raw, char *proxy_to_raw, int weight) {
    char *result = NULL;
    char *temp_join = NULL;
    char *from_proxy = NULL;
    char *proxy_to = NULL;
    char *str_weight = mx_itoa(weight);
    int temp_index;

    temp_index = mx_get_char_index(proxy_to_raw, '=');
    if (temp_index != -1) {
        temp_index--;
        proxy_to = mx_strndup(proxy_to_raw, temp_index);
    } else proxy_to = mx_strdup(proxy_to_raw);
    temp_index = mx_get_char_index(from_proxy_raw, '=');
    if (temp_index != -1) {
        temp_index--;
        from_proxy = mx_strndup(from_proxy_raw, temp_index);
    } else from_proxy = mx_strdup(from_proxy_raw);
    temp_join = mx_strjoin(from_proxy, " + ");
    result = mx_strjoin(temp_join, proxy_to);
    mx_strdel(&temp_join);
    mx_strdel(&proxy_to);
    mx_strdel(&from_proxy);
    temp_join = mx_strjoin(result, " = ");
    mx_strdel(&result);
    result = mx_strjoin(temp_join, str_weight);
    mx_strdel(&temp_join);
    mx_strdel(&str_weight);
    return result;
}

void set_literal_distance(t_graph *graph, int from, int to, int proxy) {
    char **distances = graph->literal_distances;
    int isl_count = graph->island_count;
    int weight = graph->weights[from * isl_count + to];
    char *from_proxy = distances[from * isl_count + proxy];
    char *proxy_to = distances[proxy * isl_count + to];

    if (distances[from * isl_count + to]) {
        free(distances[from * isl_count + to]);
        distances[from * isl_count + to] = NULL;
    }
    distances[from * isl_count + to] = build_literal_distance(from_proxy, proxy_to, weight);
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
                    set_literal_distance(graph, j, k, i);
                }
            }
        }
    }
}
