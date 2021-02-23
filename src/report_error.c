#include "pathfinder.h"

/**
 * Outputs errors to stderr.
 * Types of errors:
 * ERR_ARG_COUNT (-1) - if argument count is incorrect;
 * ERR_FILE_NOT_EXISTS (-2) - if file is not found;
 * ERR_FILE_IS_EMPTY (-3) - if file is empty;
 * ERR_NUM_OF_ISLANDS (-4) - if number of islands at line 1 is incorrect;
 * ERR_DUPLICATE_BRIDGES (-5) - if some bridges duplicate;
 * ERR_LEN_SUM_TOO_BIG (-6) if sum of bridge distances exceeds MAX_INTEGER;
 * @param errno - number of error to report to stderr
 * @param filename - name of file passed to the program
 */
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

    switch (errno) {
        case ERR_ARG_COUNT:
            mx_printerr("usage: ./pathfinder [filename]\n");
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
        case ERR_LEN_SUM_TOO_BIG:
            prefix = mx_strdup(error_len_sum);
            suffix = "";
            break;
        case ERR_DUPLICATE_BRIDGES:
            prefix = mx_strdup(error_dup_bridges);
            suffix = "";
            break;
        default:
            prefix = mx_strjoin(error_line_template, mx_itoa(errno));
            suffix = not_valid;
            break;
    }
    result = mx_strjoin(prefix, suffix);
    mx_printerr(result);
    mx_printerr("\n");
    mx_strdel(&prefix);
    mx_strdel(&result);
}
