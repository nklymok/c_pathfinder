#include "libmx.h"

char to_hex(int i) {
    return i >= 0 && i <= 9 ? '0' + i : 'a' + i - 10;
}

char *mx_nbr_to_hex(unsigned long nbr) {
    int len = 1;
    unsigned long temp = nbr;
    char *result;

    for (temp = nbr; temp >= 16; len++, temp /= 16);
    result = mx_strnew(len);
    result[0] = '0';
    for (int i = 0, j = len; i < len; i++, j--) {
        for (int k = 15; k >= 0; k--) {
            temp = k * mx_pow(16, j - 1);
            if ((long) (nbr - temp) >= 0) {
                nbr -= temp;
                result[i] = to_hex(k);
                break;
            }
        }
    }
    return result;
}
