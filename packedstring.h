/* SPDX-License-Identifier: MIT */

#ifndef PACKED_STRING_H
#define PACKED_STRING_H

#include <stdlib.h>
#include <stdbool.h>

struct packedstring;

struct packedstring*
packedstring_create(void);

bool
packedstring_ispacked(struct packedstring * const * const packedstring);

struct packedstring*
packedstring_strncpytopackedstring(struct packedstring * * const dst, const char * const src, const size_t size);

char*
packedstring_strncpyfrompackedstring(char *dst, struct packedstring * const * const src, const size_t size);

const
char * const
packedstring_robuf(struct packedstring * const * const packedstring, char buf[sizeof(char*)]);

size_t
packedstring_strlen(struct packedstring * const * const packedstring);

void
packedstring_destroy(struct packedstring * * const packedstring);

#endif
