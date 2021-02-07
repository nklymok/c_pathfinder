#include "libmx.h"

int mx_get_substr_index(const char *str, const char *sub) {
    bool is_sub = false;

    if (!str || !sub) return -2;
    for (int i = 0; str[i + mx_strlen(sub) - 1]; i++) {
        is_sub = true;
        for (int j = 0; sub[j]; j++) {
            if (sub[j] != str[i + j]) {
                i = i + j;
                is_sub = false;
                break;
            }
        }
        if (is_sub) return i;
    }
    return -1;
}
