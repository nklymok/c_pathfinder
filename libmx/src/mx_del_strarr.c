#include "libmx.h"

void mx_del_strarr(char ***p_arr) {
    char **arr;

	if (!p_arr)
		return;
    arr = *p_arr;
    if (arr) {
        for (int i = 0; arr[i]; i++) {
            mx_strdel(&(arr[i]));
            arr[i] = NULL;
        }
        free(arr);
    }
	p_arr = NULL;
}
