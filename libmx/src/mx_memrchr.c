#include "libmx.h"

void *mx_memrchr(const void *s, int c, size_t n) {
    unsigned char *p_s = (unsigned char *) s;
    unsigned char char_c = (unsigned char) c;

    p_s += n;
    for (size_t i = n; i > 0; i--) {
        if (*p_s == char_c) return p_s;
        p_s--;
    }
    return NULL;
}
