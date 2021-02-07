#include "libmx.h"

void *mx_memset(void *b, int c, size_t len) {
    char *p = (char *)b;
    while (len--)
        *(p++) = c;
    return b;
}

//int main() {
//    char str[50] = "GeeksForGeeks is for programming geeks.";
//    printf("%s\n", str);
//    mx_memset(str + 13, '.', 8 * sizeof(char));
//    printf("%s\n", str);
//}
