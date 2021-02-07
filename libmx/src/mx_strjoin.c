#include "libmx.h"

char *mx_strjoin(char const *s1, char const *s2) {
    if (!s1 && !s2) {
        return NULL;
    }
    if (!s1 ^ !s2) {
        return !s1 ? mx_strdup(s2) : mx_strdup(s1);
    }
    char *new_str = mx_strnew(mx_strlen(s1) + mx_strlen(s2));
    new_str = mx_strcat(mx_strcat(new_str, s1), s2);
    return new_str;
}
