#include "libmx.h"

void mx_printint(int n) {
	int size = 1;
	int numplace = 10;
	int is_negative;
	
	if (n == -2147483648) {
		mx_printstr("-2147483648");
		return;
	}
	if (n == 2147483647) {
		mx_printstr("2147483647");
		return;
	}
	if (n < 0) {
		is_negative = 1;
		n *= -1;
	} else {
		is_negative = 0;
	}

	while (n / numplace > 0) {
		size++;
		numplace *= 10;
	}

	int digits[size];

	for (int i = size - 1; i >= 0; i--) {
		digits[i] = n % 10;
		n /= 10;
	}

	if (is_negative == 1) {
		mx_printchar('-');
	}

	for (int i = 0; i < size; i++) {
		mx_printchar(digits[i] + 48);
	}
}
