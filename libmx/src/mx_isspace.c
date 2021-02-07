#include "libmx.h"

bool mx_isspace(char c) {
	for (int i = 9; i <= 13; i++)
		if (c == i) return 1;

	if (c == 32) return 1;
	return 0;
}
