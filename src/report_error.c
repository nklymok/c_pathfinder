#include "pathfinder.h"

void report_error(int errno, char *filename) {
    char *error_file_template = "error: file ";
    char *error_line_template = "error: line ";
    char *error_num_islands = "error: invalid number of islands";
    char *error_dup_bridges = "error: duplicate bridges";
    char *error_len_sum = "error: sum of bridges lengths is too big";
    char *not_exist = " does not exist";
    char *is_empty = " is empty";
    char *not_valid = " is not valid";
    char *result = NULL;
    char *prefix = NULL;
    char *suffix = NULL;

    (void)error_file_template;
    (void)error_line_template;
    (void)error_num_islands;
    (void)error_dup_bridges;
    (void)error_len_sum;
    (void)not_exist;
    (void)is_empty;
    (void)not_valid;

    switch (errno) {
        case ERR_ARG_COUNT:
            mx_printerr("usage: ./pathfinder [filename]");
            return;
        case ERR_FILE_NOT_EXISTS:
            prefix = mx_strjoin(error_file_template, filename);
            suffix = not_exist;
            break;
        case ERR_FILE_IS_EMPTY:
            prefix = mx_strjoin(error_file_template, filename);
            suffix = is_empty;
            break;
        case ERR_NUM_OF_ISLANDS:
            prefix = mx_strdup(error_num_islands);
            suffix = "";
            break;
        default:
            prefix = mx_strjoin(error_line_template, mx_itoa(errno));
            suffix = not_valid;
            break;
    }
    result = mx_strjoin(prefix, suffix);
    mx_printerr(result);
    mx_strdel(&prefix);
    mx_strdel(&result);
}
