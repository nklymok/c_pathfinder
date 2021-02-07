#include "libmx.h"

void *mx_memmove(void *dst, const void *src, size_t len) {
    char *p_dst = (char *)dst;
    char *p_src = (char *)src;
    char temp[len];

    for (size_t i = 0; i < len; i++)
        temp[i] = p_src[i];
    for (size_t i = 0; i < len; i++)
        *(p_dst++) = temp[i];
    return dst;
}
