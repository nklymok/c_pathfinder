#include "libmx.h"

int mx_memcmp(const void *s1, const void *s2, size_t n) {
    unsigned char *p_c1 = (unsigned char *)s1;
    unsigned char *p_c2 = (unsigned char *)s2;

    for (size_t i = 0; i < n && *p_c1 == *p_c2; i++, p_c1++, p_c2++);
    return (int)(*p_c1 - *p_c2);
}

//int main() {
//    char buff1[] = "Helcome to GeeksforGeeks";
//    char buff2[] = "Hello Geeks ";
//    int a;
//
//    a = mx_memcmp(buff1, buff2, sizeof(buff1));
//    printf("\n%d\n", a);
//    printf("\n%d\n", 'c' - 'l');
//}
