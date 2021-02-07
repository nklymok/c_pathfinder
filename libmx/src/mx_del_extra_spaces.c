#include "libmx.h"

int calc_len_clean(const char *s) {
	int count = 0;
	bool had_space = false;

	for (int i = 0; s[i] != '\0'; i++) {
		if (!had_space || !mx_isspace(s[i]))
			count++;
		had_space = mx_isspace(s[i]);
	}
	return count;
}

char *mx_del_extra_spaces(const char *str) {
	char *trimmed;
	char *result;
	bool had_space;

	if (!str)
        return NULL;
    trimmed = mx_strtrim(str);
    result = mx_strnew(calc_len_clean(trimmed));
	if (!trimmed || !result)
		return NULL;
	had_space = false;
	for (int i = 0, j = 0; trimmed[i] != '\0'; i++) {
		if (!had_space || !mx_isspace(trimmed[i]))
			result[j++] = trimmed[i];
		had_space = mx_isspace(trimmed[i]);
	}
	mx_strdel(&trimmed);
	return result;
}
