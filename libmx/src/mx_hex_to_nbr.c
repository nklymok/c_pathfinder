#include "libmx.h"

unsigned long hex_to_unsigned_long(int c) {
    if (c >= 65 && c <= 70)
        return c - 55;
    if (c >= 97 && c <= 102)
        return c - 87;
    if (c >= 48 && c <= 57)
        return c - 48;
    return 0;
}

unsigned long mx_hex_to_nbr(const char *hex) {
    const unsigned long SYSTEM = 16;
    unsigned long result = 0L;
    unsigned int size;

    if (!hex) return 0L;
    for (size = 0; hex[size]; size++);
    for (unsigned int i = 0; i < size; i++)
        result += hex_to_unsigned_long(hex[i]) * mx_pow(SYSTEM, size - i - 1);
    return result;
}

//#include <stdio.h>
//int main() {
//    printf("%ld\n", mx_hex_to_nbr("fAcAdE123")); // 67321585955
//}
