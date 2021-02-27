#include "libmx.h"

/*
 * Returns -2 if str is null, -1 if not found, otherwise index
 */
int mx_get_char_index(const char *str, char c) {
    if (!str) return -2;
    for (int i = 0; str[i]; i++) {
        if (str[i] == c) return i;
    }
    return -1;
}
