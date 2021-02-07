#include "libmx.h"

void *mx_memchr(const void *s, int c, size_t n) {
    unsigned char *p_s = (unsigned char *) s;
    unsigned char char_c = (unsigned char) c;

    for (size_t i = 0; i < n; i++) {
        if (*p_s == char_c) return p_s;
        p_s++;
    }
    return NULL;
}
