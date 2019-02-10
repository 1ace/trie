/* SPDX-License-Identifier: MIT */

#include "trie.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct trie {
   char *prefix;
   void *value;
   unsigned char nchildren;
   struct trie *children;
};

static
void
trie_init(struct trie *trie)
{
   memset(trie, 0, sizeof(struct trie));
}

struct trie *
trie_create(void)
{
   struct trie *trie = malloc(sizeof(struct trie));
   trie_init(trie);
   return trie;
}

void
trie_destroy(struct trie * const trie)
{
   if (!trie) {
      return;
   }

   if (trie->prefix)
      free(trie->prefix);

   if (trie->children)
      free(trie->children);

   free(trie);
}

static
void
trie_print(const struct trie * const trie,
           const int level)
{
   for (int i = 0; i < level; ++i)
      printf("%s", "--");
   printf("%s => %p\n", trie->prefix, trie->value);
   for (int i = 0; i < trie->nchildren; ++i)
      trie_print(&trie->children[i], level+1);
}

static
int
trie_cmp(const char *key,
         const struct trie *trie)
{
   char *prefix = "";
   if (trie && trie->prefix)
      prefix = trie->prefix;
   return key[0] > prefix[0] ? 1 : (key[0] == prefix[0] ? 0 : -1);
}

static
bool
trie_bsearch(const char *key,
             const struct trie *list,
             const size_t len,
             size_t * const index)
{
   size_t s = 0, e = len, c;
   int cmp;
   while (c = (s+e)/2, cmp = trie_cmp(key, &list[c]), cmp && c > 0 && c < e)
   {
      if (cmp > 0)
         s = c + 1;
      else
         e = c;
   }
   if (index)
      *index = c;
   return cmp == 0;
}

bool
trie_insert(struct trie * const trie,
            const char * const name,
            void * const value)
{
   printf("insert %s => %p\n", name, value);
   trie_print(trie, 0);
   if (!value)
      return false;

   if (!name)
      return false;

   if (!trie->prefix)
   {
      printf("replace root\n");
      trie->prefix = strcpy(calloc(strlen(name)+1, sizeof(char)), name);
      trie->value = value;
      return true;
   }

   struct trie *node = trie;

   for (const char *c = name; *c;)
   {
      const char *d = node->prefix;
      for (; *d && *c && *d == *c; ++d, ++c);
      if (*d) {
         // we didn't reach the end of node->prefix
         // we must split
         struct trie *newchild = trie_create();
         newchild->prefix = strcpy(calloc(strlen(d)+1, sizeof(char)), d);
         newchild->value = node->value;
         newchild->nchildren = node->nchildren;
         newchild->children = node->children;

         size_t prefixlen = d-node->prefix;
         node->prefix = realloc(node->prefix, prefixlen+1);
         node->prefix[prefixlen] = 0;
         node->value = NULL;
         node->nchildren = 1;
         node->children = newchild;
      }
      if (!*c) {
         // we reached the end of node->prefix and the end of name, the current node is the one we were looking for
         // replace/update the value
         break;
      }

      size_t index;
      const size_t len = node->nchildren;
      if (!trie_bsearch(c, node->children, len, &index))
      {
         ++node->nchildren;
         node->children = realloc(node->children, (node->nchildren)*sizeof(struct trie));
         if (index < len)
            memmove(&node->children[index+1], &node->children[index], (len-index)*sizeof(struct trie));

         trie_init(&node->children[index]);
         node->children[index].prefix = strcpy(calloc(strlen(c)+1, sizeof(char)), c);
         node = &node->children[index];
         break;
      }
      node = &node->children[index];
   }

   node->value = value;

   printf("inserted %s => %p\n", name, value);
   trie_print(trie, 0);
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

   for (const char *c = name; *c;)
   {
      if (node->prefix && node->prefix[0])
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

      size_t index;
      if (!trie_bsearch(c, node->children, node->nchildren, &index))
         return false;

      node = &node->children[index];
   }

   if (value)
      *value = node->value;
   return true;
}
