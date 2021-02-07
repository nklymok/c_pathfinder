#include "libmx.h"

void *mx_memccpy(void *restrict dst, const void *restrict src, int c, size_t n) {
    unsigned char *p_dst = (unsigned char *)dst;
    unsigned char *p_src = (unsigned char *)src;

    for (size_t i = 0; i < n; i++, p_dst++, p_src++) {
        *p_dst = *p_src;
        if (*p_dst == c) break;
    }
    return dst;
}
