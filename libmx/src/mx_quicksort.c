#include "libmx.h"

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int *arr, int left, int right, int *swap_count) {
    int pivot = arr[right]; // pivot, the element on the right
    int i = left; // looks for larger values than pivot
    int j = right - 1; // looks for smaller values than pivot

    // if left and right are adjacent, swap if needed and return -1
    if (i == j) {
        if (arr[i] > arr[i + 1]) {
            swap(&arr[i], &arr[i + 1]);
            (*swap_count)++;
        }
        return -1;
    }
    while (i <= j) {
        if (arr[i] > pivot) {
            if (arr[j] < pivot) {
                swap(&arr[i], &arr[j]);
                (*swap_count)++;
                i++;
                j--;
            }
            else j--;
        }
        else i++;
    }
    if (arr[i] > arr[right]) {
        swap(&arr[i], &arr[right]);
        (*swap_count)++;
    }
    return i;
}

int mx_quicksort(int *arr, int left, int right) {
    int pivot;
    int swaps = 0;

    if (!arr) return -1;
    if (left < right) {
        pivot = partition(arr, left, right, &swaps);
        if (pivot == -1) {
            return swaps;
        }
        swaps += mx_quicksort(arr, left, pivot - 1);
        swaps += mx_quicksort(arr, pivot + 1, right);
    }
    return swaps;
}
