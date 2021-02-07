#include "libmx.h"

int mx_count_words(const char *str, char delimiter) {
	int result = 0;

	if (!str) return -1;
	for (int i = 0; str[i] != '\0'; i++) {
		// skip all delimiters
		for (; str[i] == delimiter; i++);
		if (str[i] != '\0') result++;
		// skip to delimiters or end
		for (; str[i] != '\0' && str[i] != delimiter; i++); 
		//stop if end of line
		if (str[i] == '\0') break;
	}
	return result;
}
