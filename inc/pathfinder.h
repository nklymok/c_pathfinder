#pragma once

#include "libmx.h"

#define ERR_ARG_COUNT -1
#define ERR_FILE_NOT_EXISTS -2
#define ERR_FILE_IS_EMPTY -3
#define ERR_NUM_OF_ISLANDS -4
#define ERR_DUPLICATE_ISLANDS -5
#define ERR_LEN_SUM_TOO_BIG -6

typedef struct s_graph {
    int island_count;
    int len_sum;
} t_graph;

bool handle_errors(int argc, char **argv, t_graph *graph);
void report_error(int errno, char *filename);
