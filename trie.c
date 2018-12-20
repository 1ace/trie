/* SPDX-License-Identifier: MIT */

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#include "macros.h"

#include "trie.h"

#define TRIE_ALNUM_LEN 63 // [a-zA-Z0-9_]

struct trie {
   void *value;
   struct trie *children[TRIE_ALNUM_LEN];
};

struct trie *
trie_create(void)
{
   return malloc(sizeof(struct trie));
}

void
trie_destroy(struct trie * const trie)
{
   if (!trie)
      return;

   for (size_t i = 0; i < TRIE_ALNUM_LEN; i++)
      trie_destroy(trie->children[i]);

   free(trie);
}

static inline bool
trie_index(char c, size_t *index)
{
   size_t i;

   if ('a' <= c && c <= 'z')
      i = c - 'a';

   else if ('A' <= c && c <= 'Z')
      i = c - 'A' + 26;

   else if ('0' <= c && c <= '9')
      i = c - '0' + 52;

   else if (c == '_')
      i = 62;

   else {
      assert(!"unsupported char");
      return false;
   }

   assert(i < TRIE_ALNUM_LEN);
   *index = i;
   return true;
}

bool
trie_insert(struct trie * const trie,
            const char * const name,
            void * const value)
{
   struct trie *node = trie;

   if (!name || !name[0])
      return false;

   for (const char *c = name; *c; c++)
   {
      size_t index;

      if (!trie_index(*c, &index))
         return false;

      if (!node->children[index])
         node->children[index] = calloc(1, sizeof(*node->children[index]));

      if (!node->children[index])
         return false;

      node = node->children[index];
   }

   if (node->value)
      return false;

   node->value = value;
   return true;
}

bool
trie_fetch(const struct trie * const trie,
           const char * const name,
           void ** const value)
{
   const struct trie *node = trie;

   if (!name || !name[0])
      return false;

   for (const char *c = name; *c; c++)
   {
      size_t index;

      if (!trie_index(*c, &index))
         return false;

      if (!node->children[index])
         return false;

      node = node->children[index];
   }

   if (value)
      *value = node->value;

   return true;
}

