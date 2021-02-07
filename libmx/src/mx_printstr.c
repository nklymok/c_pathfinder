#include "libmx.h"

int mx_strlen(const char *s);

void mx_printstr(const char *s) {
	if (!s) return;
	for (int i = 0; i < mx_strlen(s); i++) {
		write(1, &s[i], 1);	
	}
}

//int main(void) {
//	mx_printstr("hello world");
//}

