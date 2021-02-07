#include "libmx.h"

char *mx_strtrim(const char *str) {
	int i;
	int start_index;
	int end_index;
    char *result;

    if (!str) {
        return NULL;
    }
	for(i = 0; mx_isspace(str[i]); i++);
	start_index = i;
	for(i = mx_strlen(str) - 1; mx_isspace(str[i]); i--);
	end_index = i;
	result = mx_strnew(end_index - start_index + 1);
	if (!result)
		return NULL;
	for (i = start_index; i <= end_index; i++)
		result[i - start_index] = str[i];
	return result;
}
