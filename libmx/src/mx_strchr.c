#include "libmx.h"

char *mx_strchr(const char *s, int c) {
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == c) {
            return (char *)&s[i];
        }
    }
    
    return NULL;
}

/*int main() {
	char str1[] = "abcde";
	printf("%c\n", *mx_strchr(str1, 'a'));
	printf("%c\n", *mx_strchr(str1, 'b'));
	printf("%c\n", *mx_strchr(str1, 'e'));
	printf("%c\n", *mx_strchr(str1, 'z'));
	char str2[] = "o Neo";
	printf("%c\n", *mx_strchr(str2, 'y'));
}*/

