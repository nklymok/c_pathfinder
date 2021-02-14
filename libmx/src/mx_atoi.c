#include "libmx.h"

int mx_atoi(const char *str) {
	bool reached_num = false;
	bool is_negative = false;
	bool is_positive = false;
	int result = 0;

	for (int i = 0; str[i] != '\0'; i++) {
		if (mx_isspace(str[i])) {
			if (reached_num) break;
			else for (; mx_isspace(str[i]); i++);
		}
		if (!mx_isdigit(str[i])) {
			if (reached_num) {
				break;
			}
			if (str[i] == '-') {
				if (is_negative || is_positive) return 0;
				is_negative = true;
				continue;
			} else if (str[i] == '+') {
				if (is_negative || is_positive) return 0;
				is_positive = true;
				continue;
			} else {
				break;
			}
		}

		reached_num = true;
		int digit = str[i] - 48;
		result = result * 10 + digit;
	}	

	return is_negative ? -result : result;
}
