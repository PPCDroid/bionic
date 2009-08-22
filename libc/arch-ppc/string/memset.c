#include <string.h>

void *memset(void *b, int c, size_t n)
{
	char *p;

	if (n == 0)
		return b;

	while (n--)
		*p++ = (char)c;

	return b;
}

