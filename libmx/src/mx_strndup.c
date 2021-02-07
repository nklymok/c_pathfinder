#include "libmx.h"
		
char *mx_strndup(const char *str, size_t n) {
	if (!str) return NULL;
	return mx_strncpy(mx_strnew(n), str, n);
}
