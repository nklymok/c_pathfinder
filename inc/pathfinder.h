#pragma once

#include "libmx.h"

#define ERR_ARG_COUNT -1
#define ERR_FILE_NOT_EXISTS -2
#define ERR_FILE_IS_EMPTY -3
#define ERR_NUM_OF_ISLANDS -4
#define ERR_DUPLICATE_BRIDGES -5
#define ERR_LEN_SUM_TOO_BIG -6

#define MAX_INT 2147483647

typedef struct s_graph {
    int island_count;
    long len_sum;
    int last_filled_index;
    char **islands;
    char **literal_paths;
    int *weights;
} t_graph;

bool handle_errors(int argc, char **argv, t_graph *graph);
void report_error(int errno, char *filename);
void find_paths(t_graph *graph);
