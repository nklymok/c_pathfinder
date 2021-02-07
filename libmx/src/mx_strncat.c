#include "libmx.h"

char *mx_strncat(char *restrict s1, const char *restrict s2, size_t len) {
    size_t i = 0;
    int j = 0;

    for (i = 0, j = mx_strlen(s1); i < len; i++) {
        s1[j + i] = s2[i];
    }
    s1[j + i] = '\0';
    return s1;
}
