#include "libmx.h"

bool mx_contains_str(const char *needle, const char **str) {
	bool result = false;

	if (str && needle) {
	    for (int i = 0; str[i]; i++) {
	        if (mx_strcmp(needle, str[i]) == 0) {
	            result = true;
	            break;
	        }
	    }
	}
	return result;
}
