#include "packedstring.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

static
void
packstring_debug_prinf(struct packedstring *s, size_t n)
{
	printf("%18p ", s);
	for (int i = 0; i < sizeof(char *); ++i)
		printf("%02hhx ", ((char *)&s)[i]);
	// printf("%.*s\n", (int)n, (char*)&s);
	if (packedstring_ispacked(&s))
	{
		printf("embeds %d bytes: ", packedstring_strlen(&s));
	}
	else
		printf("points to buff: ");

	if (packedstring_ispacked(&s))
	{
		char buf[sizeof(char*)] = {0};
		packedstring_strncpyfrompackedstring(buf, &s, sizeof(char*));
		printf("%s", buf);
	}
	else
		printf("%s", (char*)s);
	printf("\n");
}

int main(int argc, char const *argv[])
{
	struct packedstring *s = packedstring_create();
	size_t n = 4;
	packedstring_strncpytopackedstring(&s, "foo", n);
	packstring_debug_prinf(s, n);
	n = 7;
	packedstring_strncpytopackedstring(&s, "strmax", n);
	packstring_debug_prinf(s, n);
	n = 8;
	packedstring_strncpytopackedstring(&s, "strmaxx", n);
	packstring_debug_prinf(s, n);
	n = 10;
	packedstring_strncpytopackedstring(&s, "0xbadfood", n);
	packstring_debug_prinf(s, n);
	packedstring_destroy(&s);
	return 0;
}