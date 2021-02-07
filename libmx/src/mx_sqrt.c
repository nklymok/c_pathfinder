#include "libmx.h"

int mx_sqrt(int x) {
    int temp;

    if (x == 1) return 1;
    for (int i = 0; i < x; i++) {
        temp = i * i;
        if (temp > x) return 0;
        if (i * i == x) return i;
    }

    return 0;
}
