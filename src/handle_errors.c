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
        // TODO check line syntax
        // TODO check for duplicates
        // TODO check for len sum too big
        printf("%s\n", current_line);
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
