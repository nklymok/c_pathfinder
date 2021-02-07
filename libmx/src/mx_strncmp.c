#include "libmx.h"

int mx_strncmp(const char *s1, const char *s2, int n) {
	int i = 0;
	while (i < n - 1) {
		if ((s1[i] == '\0' || s2[i] == '\0')) break;
		if (s1[i] != s2[i]) break;
		i++;
	}

	return n > 0 ? s1[i] - s2[i] : 0;
}
