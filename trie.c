/* SPDX-License-Identifier: MIT */

#include "trie.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
   char *prefix;
   void *value;
   struct trie *children[255];
};

struct trie *
trie_create(void)
{
   return calloc(1, sizeof(struct trie));
}

void
trie_destroy(struct trie * const trie)
{
   if (!trie) {
      return;
   }

   free(trie->prefix);

   for (unsigned int i = 0; i < 255; i++) {
      trie_destroy(trie->children[i]);
   }

   free(trie);
}

static
bool
has_children(struct trie * const trie)
{
   for (unsigned int i = 0; i < 255; ++i)
   {
      if (trie->children[i])
         return true;
   }
   return false;
}

bool
trie_insert(struct trie * const trie,
            const char * const name,
            void * const value)
{
   if (!value)
      return false;

   struct trie *node = trie;

   if (!name)
      return false;

   for (const char *c = name; *c; ++c)
   {
      if (!node->value && !has_children(node))
      {
         node->prefix = strcpy(calloc(strlen(c)+1, sizeof(char)), c);
         break;
      }

      if (node->prefix)
      {
         const char *d = node->prefix;
         for (; *d && *c && *d == *c; ++d, ++c);
         if (*d) {
            // we didn't reach the end of node->prefix
            // we must split
            struct trie *newchild = trie_create();
            size_t suffixlen = strlen(d);
            newchild->prefix = suffixlen ? strcpy(calloc(suffixlen, sizeof(char)), d+1) : NULL;
            newchild->value = node->value;
            memcpy(newchild->children, node->children, sizeof(newchild->children));

            size_t prefixlen = d-node->prefix;
            node->prefix = realloc(node->prefix, prefixlen+1);
            char pivot = node->prefix[prefixlen];
            node->prefix[prefixlen] = 0;
            node->value = NULL;
            memset(node->children, 0, sizeof(node->children));
            node->children[pivot-1] = newchild;
         }
         if (!*c) {
            // we reached the end of node->prefix and the end of name, the current node is the one we were looking for
            // replace/update the value
            break;
         }
      }

      if (!node->children[(*c)-1])
      {
         node->children[(*c)-1] = trie_create();
      }

      node = node->children[(*c)-1];
   }

   node->value = value;
   return true;
}

bool
trie_fetch(const struct trie * const trie,
           const char * const name,
           void ** const value)
{
   const struct trie *node = trie;

   if (!name)
      return false;

   for (const char *c = name; *c; ++c)
   {
      if (node->prefix)
      {
         const char *d = node->prefix;
         for (; *d && *c && *d == *c; ++d, ++c);
         if (*d) {
            // we didn't reach the end of node->prefix
            return false;
         }
         if (!*c) {
            // we reached the end of node->prefix and the end of name, the current node is the one we were looking for
            break;
         }
      }

      if (!node->children[(*c)-1])
         return false;

      node = node->children[(*c)-1];
   }

   if (!value)
      return false;

   *value = node->value;
   return true;
}
