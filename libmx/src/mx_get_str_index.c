#include "libmx.h"

int mx_get_str_index(const char *needle, const char **str) {
    if (!str || !needle) return -2;
    for (int i = 0; str[i]; i++) {
        if (mx_strcmp(str[i], needle) == 0)  return i;
    }
    return -1;
}
