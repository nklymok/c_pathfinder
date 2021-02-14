#include "pathfinder.h"

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

bool first_line_correct(char *first_line) {
    int first_line_as_int;
    // check for non-digits for first line
    for (int i = 0; i < mx_strlen(first_line); i++) {
        if (!mx_isdigit(first_line[i])) {
            return false;
        }
    }
    first_line_as_int = mx_atoi(first_line);
    // check for negative
    if (first_line_as_int < 1) {
        return false;
    }
    return true;
}

// TODO check line (duplicates, only alpha, len)
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

// result[0] - island1, result[1] - island2, result[2] - cost
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

bool parse_bridge_syntax(char *line, t_graph *graph) {
    char **islands;
    char *island1;
    char *island2;
    int cost;

    if (mx_strlen(line) < 5) return false;
    if (!check_bridge_syntax(line)) return false;
    islands = parse_islands(line);
    island1 = islands[0];
    island2 = islands[1];
    cost = mx_atoi(islands[2]);
    // TODO add island1, island2 to graph
    //  Check for len > MAX_INT
    graph->len_sum += cost;

    printf("island1: %s | island2: %s | cost: %d\n", island1, island2, cost);
    printf("total cost: %ld\n", graph->len_sum);
    mx_del_strarr(&islands);
    return true;
}

int check_lines(char *filename, t_graph *graph) {
    int fd;
    char *current_line = mx_strnew(100);

    fd = open(filename, O_RDONLY);
    mx_read_line(&current_line, 1, '\n', fd);
    if (!first_line_correct(current_line)) {
        mx_strdel(&current_line);
        return 1;
    }
    graph->island_count = mx_atoi(current_line);
    for (int i = 0; i < graph->island_count; i++) {
        if (mx_read_line(&current_line, 1, '\n', fd) < 0) {
            return ERR_NUM_OF_ISLANDS;
        }
        if (!parse_bridge_syntax(current_line, graph)) {
            return i + 2;
        }
        if (graph->len_sum > MAX_INT) {
            return ERR_LEN_SUM_TOO_BIG;
        }
        // TODO put islands into graph
        // TODO check for duplicates
        // TODO check for len sum too big
    }
    // if hasn't reached EOF
    if (mx_read_line(&current_line, 1, '\n', fd) != -1) {
        return ERR_NUM_OF_ISLANDS;
    }
    mx_strdel(&current_line);
    return 0;
}

// checks arg count, whether file exists or empty
// checks first line (and sets island_count)
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
