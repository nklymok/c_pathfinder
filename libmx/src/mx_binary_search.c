#include "libmx.h"

int mx_binary_search(char **arr, int size, const char *s, int *count) {
        int left_index = 0;
        int right_index = size - 1;
        int middle_index;
        int cmp_diff;
        char *middle_val;

        while (left_index <= right_index) {
            (*count)++;
            middle_index = (left_index + right_index) / 2;
            middle_val = arr[middle_index];
            cmp_diff = mx_strcmp(s, middle_val);
            if (cmp_diff > 0)
                left_index = middle_index + 1;
            else if (cmp_diff < 0)
                right_index = middle_index - 1;
            else return middle_index;
        }
        *count = 0;
        return -1;
}
