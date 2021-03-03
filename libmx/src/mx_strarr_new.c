#include "libmx.h"

char **mx_strarr_new(const int size) {
    char **p;
    
	if (size < 1) {
		return NULL;
	}
    p = (char **)malloc(sizeof(char *) *
                                     (size + 1));
    if (!p) {
        return NULL;
    }
    for (int i = 0; i < size + 1; i++) {
        p[i] = NULL;
    }
    
	return p;
}
