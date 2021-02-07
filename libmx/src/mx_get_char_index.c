#include "libmx.h"

int mx_get_char_index(const char *str, char c) {
    if (!str) return -2;
    for (int i = 0; str[i]; i++) {
        if (str[i] == c) return i;
    }
    return -1;
}

//int main(void) {
//    char *word = "hello world";
//    printf("%d\n", mx_get_char_index(word, 'h'));
//    printf("%d\n", mx_get_char_index(word, ' '));
//    printf("%d\n", mx_get_char_index(word, 'w'));
//    printf("%d\n", mx_get_char_index(word, 'd'));
//    printf("%d\n", mx_get_char_index(word, '!'));
//
//    char *word1 = NULL;
//    printf("%d\n", mx_get_char_index(word1, 'o'));
//}
