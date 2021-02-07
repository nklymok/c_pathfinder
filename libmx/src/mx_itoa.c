#include "libmx.h"

char *mx_itoa(int n) {
	int size = 1;
	int numplace = 10;
	int is_negative;
	char *result;

	if (n == -2147483648) {
		result = mx_strdup("-2147483648");
		return result;
	}
	if (n == 2147483647) {
		result = mx_strdup("2147483647");
		return result;
	}
	if (n < 0) {
		is_negative = 1;
		n *= -1;
	} else
		is_negative = 0;
	while (n / numplace > 0) {
		size++;
		numplace *= 10;
	}
	int digits[size];
	result = is_negative ? mx_strnew(size  + 1) : mx_strnew(size);
	for (int i = size - 1; i >= 0; i--, n /= 10)
		digits[i] = n % 10;
	if (is_negative == 1)
	    result[0] = '-';
	for (int i = 0; i < size; i++)
        result[i + is_negative] = digits[i] + 48;
	return result;
}

