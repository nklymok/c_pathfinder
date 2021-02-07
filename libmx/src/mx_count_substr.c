#include "libmx.h"

int mx_count_substr(const char *str, const char *sub) {
	int count = 0;
	const char *start = str;

	if (!str || !sub) return -1;
	if (mx_strlen(sub) == 0) return 0;
	while (*start != '\0') {
		start = mx_strstr(start, sub);
		if (start) {
			start += mx_strlen(sub);
			count++;
		} else {	
			break;
		}
	}

	return count;
}
