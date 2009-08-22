#include <string.h>

void *memcpy(void *s1, const void *s2, size_t n)
{
	char *p1;
	const char *p2;

	if (n == 0)
		return s1;

	p1 = s1;
	p2 = s2;
	while (n--)
		*p1++ = *p2++;

	return s1;
}

