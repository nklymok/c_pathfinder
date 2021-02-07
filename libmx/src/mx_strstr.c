#include "libmx.h"

char *mx_strstr(const char *s1, const char *s2) {	
	int s2_len = mx_strlen(s2);
    const char *start;

    if (s2_len == 0)
		return (char *)s1;
	start = s1;
	while (start) {
		if (mx_strncmp(start, s2, s2_len) == 0)
            return (char *) start;
		start = mx_strchr(start + 1, s2[0]);
	}
	return NULL;
}
