#include "libmx.h"

char *mx_strnew(const int size) {
	if (size < 1) {
		return NULL;
	}
	char *p = (char *) malloc(size + 1);
	if (!p) {
		return NULL;
	}
	for (int i = 0; i < size + 1; i++) {
		p[i] = '\0';
	}
	return p;
}

