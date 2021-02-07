#include "libmx.h"

char *mx_replace_substr(const char *str, const char *sub, const char *replace) {
    int str_len;
    int sub_len;
    int sub_count;
    int replace_len;
    int new_str_len;
    char *result;
    int end_pos = 0;

    // error handling
    if (!sub || !str || !replace) return NULL;
    sub_count = mx_count_substr(str, sub);
    if (sub_count == 0) return mx_strdup(str);
    // initializing variables
    str_len = mx_strlen(str);
    sub_len = mx_strlen(sub);
    replace_len = mx_strlen(replace);
    new_str_len = str_len - (sub_len * sub_count) + (replace_len * sub_count);
    result = mx_strnew(new_str_len);
    // the algorithm per se
    for (int subs = 0, start = 0, pos = 0; subs < sub_count; subs++, start = pos) {
        pos = mx_get_substr_index(str + pos, sub) + pos;
        mx_strncat(result, str + start, pos - start);
        mx_strcat(result, replace);
        if (pos != -1) {
            pos += sub_len;
            end_pos = pos;
        }
    }
    mx_strcat(result, str + end_pos);
    return result;
}
