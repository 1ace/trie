/* SPDX-License-Identifier: MIT */

#ifndef UTIL_TRIE_H
#define UTIL_TRIE_H

#include <stdbool.h>

#include "macros.h"

struct trie;

struct trie *
trie_create(void);

void
trie_destroy(struct trie *trie);

MUST_CHECK bool
trie_insert(struct trie *trie,
            const char *name,
            void *value);

MUST_CHECK bool
trie_fetch(const struct trie *trie,
           const char *name,
           void ** const value);

#endif
