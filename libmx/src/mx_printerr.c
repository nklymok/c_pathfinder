#include "libmx.h"

int mx_strlen(const char *s);

void mx_printerr(const char *s) {
	if (!s) return;
	for (int i = 0; i < mx_strlen(s); i++) {
		write(2, &s[i], 1);
	}
}
