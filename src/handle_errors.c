/*
 * handle_errors provides a few functions that,
 * apart of error handling, fills in given graph(!).
 * entry point that shows the process of error handling
 * can be seen in handle_errors(int argc, char **argv, t_graph graph)
 */

#include "pathfinder.h"

/**
 * A program should start with 2 arguments:
 * 1) program name
 * 2) file name
 * @param argc - the count of program arguments
 * @return true if argument count is correct, otherwise false.
 */
bool check_args(int argc) {
    if (argc != 2) {
        report_error(ERR_ARG_COUNT, NULL);
        return false;
    }
    return true;
}

bool check_file_exists(char *filename) {
    if (!mx_file_exists(filename)) {
        report_error(ERR_FILE_NOT_EXISTS, filename);
        return false;
    }
    return true;
}

bool check_file_is_empty(char *filename) {
    if (mx_file_is_empty(filename)) {
        report_error(ERR_FILE_IS_EMPTY, filename);
        return false;
    }
    return true;
}

/**
 * Checks the first line:
 * It should contain only a positive number
 * @param first_line - pointer to the first line
 * @return true if correct format, otherwise false.
 */
bool first_line_correct(char *first_line) {
    long first_line_as_long;

    // check for non-digits for first line
    for (int i = 0; i < mx_strlen(first_line); i++) {
        if (!mx_isdigit(first_line[i])) {
            return false;
        }
    }
    first_line_as_long = mx_atol(first_line);
    // check for negative
    if (first_line_as_long < 1) {
        return false;
    }
    return true;
}

/**
 * Checks every line except the first one.
 * The line should match the following format: A-B,p, where:
 *      A is the name of the first island (only abc)
 *      B is the name of the second island (only abc)
 *      p is the distance between A and B (only positive decimal number)
 * @param line - line to check
 * @return returns false in case of any described errors, otherwise false.
 */
bool check_bridge_syntax(char *line) {
    bool comma_met = false;
    bool hyphen_met = false;
    bool digit_met = false;

    for (int i = 0; i < mx_strlen(line); i++) {
        if (!mx_isalpha(line[i])) {
            if (line[i] != ',' && line[i] != '-') {
                if (hyphen_met && comma_met && mx_isdigit(line[i])) {
                    digit_met = true;
                } else {
                    return false;
                }
            }
            if (line[i] == ',') {
                if (comma_met) return false;
                else comma_met = true;
            }
            if (line[i] == '-') {
                if (hyphen_met) return false;
                else hyphen_met = true;
            }
        } else if (digit_met) return false;
    }
    return true;
}

/**
 * parses islands and distance from line.
 * Should be called only after checking line syntax with check_bridge_syntax
 * @param line - the line to be checked
 * @return the array of strings, where: \
 *      [0] - name of island1, \
 *      [1] - name of island2, \
 *      [2] - distance (so-called cost)
 */
char **parse_islands(char *line) {
    char **hyphen_separated = mx_strsplit(line, '-');
    char *island1 = hyphen_separated[0];
    char *island2;
    char **temp = mx_strsplit(hyphen_separated[1], ',');
    char** result = malloc(sizeof(char *) * 4);

    island2 = temp[0];
    result[0] = mx_strdup(island1);
    result[1] = mx_strdup(island2);
    result[2] = mx_strdup(temp[1]);
    result[3] = NULL;

    mx_del_strarr(&temp);
    mx_del_strarr(&hyphen_separated);
    return result;
}

bool check_cost_already_filled(int island1_index, int island2_index, t_graph *graph) {
    int *weights = graph->weights;

    if (weights[island1_index * graph->island_count + island2_index] != -1 ||
        weights[island2_index * graph->island_count + island1_index] != -1) {
        return true;
    }
    return false;
}

int parse_bridge_syntax(char *line, t_graph *graph) {
    char **islands = NULL;
    char *island1 = NULL;
    char *island2 = NULL;
    int island1_index;
    int island2_index;
    long cost;

    if (mx_strlen(line) < 5) return -1;
    if (!check_bridge_syntax(line)) return -1;
    islands = parse_islands(line);
    island1 = islands[0];
    island2 = islands[1];
    if (mx_strcmp(island1, island2) == 0) return -1;
    cost = mx_atol(islands[2]);
    graph->len_sum += cost;
    // If either of islands is new, check for island count & add it
    if (!mx_contains_str(island1, (const char **) graph->islands)) {
        if (graph->last_filled_index >= graph->island_count) return ERR_NUM_OF_ISLANDS;
        graph->islands[graph->last_filled_index++] = mx_strdup(island1);
    }
    if (!mx_contains_str(island2, (const char **) graph->islands)) {
        if (graph->last_filled_index >= graph->island_count) return ERR_NUM_OF_ISLANDS;
        graph->islands[graph->last_filled_index++] = mx_strdup(island2);
    }
    island1_index = mx_get_str_index((const char *) island1,
                                     (const char **) graph->islands);
    island2_index = mx_get_str_index((const char *) island2,
                                     (const char **) graph->islands);
    // Path from island1 to island2, i.e "A -> B"
    set_initial_path(graph, island1_index, island2_index);
    // Set zero cost for island to itself, both ways(!)
    graph->weights[island1_index * graph->island_count + island1_index] =
            0;
    graph->weights[island2_index * graph->island_count + island2_index] =
            0;
    // Set cost between islands, both ways(!), or ERR if already filled
    if (check_cost_already_filled(island1_index, island2_index, graph))
        return ERR_DUPLICATE_BRIDGES;
    graph->weights[island1_index * graph->island_count + island2_index] =
            (int) cost;
    graph->weights[island2_index * graph->island_count + island1_index] =
            (int) cost;
    // Cost from island1 to island2, i.e. "5"
    set_initial_distance(graph, island1_index, island2_index);
    mx_del_strarr(&islands);
    return 0;
}

/**
 * Fills all distances between islands with -1.
 * -1 is used to show that there is no connection between islands.
 * If there is a connection, other functions will
 *      replace -1 with a real value.
 * @param weights - pointer to array that contains weights (distances)
 *                  between islands
 * @param arr_size - size of weights array
 */
void fill_weights(int *weights, int arr_size) {
    for (int i = 0; i < arr_size; i++) {
        for (int j = 0; j < arr_size; j++) {
            weights[arr_size * i + j] = -1;
        }
    }
}

/**
 * Checks the file lines for all possible errors.
 * This function calls other functions to check line syntax and parse data.
 * After finishing, graph will be filled with initial data from file.
 * @param filename - a file that contains data to parse later
 * @param graph - an empty t_graph
 * @return 0 - if finished correctly, \
 *         ERR_LEN_SUM_TOO_BIG - if total sum of distances \
 *                               between islands is too big. \
 *         a positive number - index of incorrect line.
 */
int check_lines(char *filename, t_graph *graph) {
    int fd;
    char *current_line = mx_strnew(100);
    int line_count = 0;
    int parse_result = 0;

    fd = open(filename, O_RDONLY);
    // parsing line 1
    mx_read_line(&current_line, 1, '\n', fd);
    if (!first_line_correct(current_line)) {
        mx_strdel(&current_line);
        return 1;
    }
    // allocating graph children
    graph->island_count = mx_atoi(current_line);
    graph->islands = (char **)malloc(sizeof(char *) *
            (graph->island_count + 1));
    graph->islands[graph->island_count] = NULL;
    /*
     * This fragment should use formula (n*(n - 1))/2 to calculate
     *  the maximum amount of routes there might be (and add 1 for NULL).
     *  However, since I use matrix, I more than double memory used.
     *  I haven't come up with the idea how to implement it yet.
     *  Here is this fragment the way it should be:
     */
//    graph->literal_paths = (char **)malloc(sizeof(char *) *
//            (((graph->island_count * (graph->island_count - 1)) / 2) + 1));
    graph->literal_paths = (char **)malloc(sizeof(char *) *
            (graph->island_count * graph->island_count + 1));
    graph->literal_distances = (char **)malloc(sizeof(char *) *
            (graph->island_count * graph->island_count + 1));
    graph->weights = (int *)malloc(sizeof(int) * (graph->island_count * graph->island_count));
    fill_weights(graph->weights, graph->island_count);
    // parsing rest of the lines
    while (mx_read_line(&current_line ,1, '\n', fd) != -1) {
        parse_result = parse_bridge_syntax(current_line, graph);
        if (parse_result == -1) {
            return line_count + 2;
        } else if (parse_result != 0) {
            return parse_result;
        }
        if (graph->len_sum > MAX_INT) {
            return ERR_LEN_SUM_TOO_BIG;
        }
        line_count++;
    }
    close(fd);
    mx_strdel(&current_line);
    return 0;
}

/**
 * Entry poing for error handling.
 * In case of errors, calls report_error that shows the error in stderr.
 * @param argc - argument count passed to program
 * @param argv - arguments passed to program
 * @param graph - an empty graph
 * @return true if finished successfully, otherwise false.
 */
bool handle_errors(int argc, char **argv, t_graph *graph) {
    char *filename;

    (void) graph;
    if (!check_args(argc)) return false;
    filename = argv[1];
    if (!check_file_exists(filename)) return false;
    if (!check_file_is_empty(filename)) return false;
    int incorrect_line = check_lines(filename, graph);
    if (incorrect_line != 0) {
        report_error(incorrect_line, filename);
        return false;
    }

    return true;
}
