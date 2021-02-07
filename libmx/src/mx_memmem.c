#include "libmx.h"

void *mx_memmem(const void *big, size_t big_len, const void *little, size_t little_len) {
    unsigned char *start = (unsigned char *) big;
    unsigned char *needle = (unsigned char *) little;
    size_t curr_pos = 0;
    bool is_met;

    while (curr_pos + little_len < big_len) {
        is_met = true;
        for (size_t i = 0; i < little_len; i++) {
            if (*(start + curr_pos + i) != *(needle + i)) {
                is_met = false;
                break;
            }
        }
        if (is_met) return (void *)(start + curr_pos);
        curr_pos++;
    }
    return NULL;
}
