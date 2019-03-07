/* SPDX-License-Identifier: MIT */

#include "trie.h"

#include "packedstring.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct trie {
   struct packedstring *prefix;
   void *value;
   unsigned char nchildren;
   struct trie *children;
};

static
void
trie_init(struct trie *trie)
{
   memset(trie, 0, sizeof(struct trie));
   trie->prefix = packedstring_create();
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

   packedstring_destroy(&trie->prefix);

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
   char buf[80] = {0};
   packedstring_strncpyfrompackedstring(buf, &trie->prefix, sizeof(buf)-1);
   printf("%s => %p\n", buf, trie->value);
   for (int i = 0; i < trie->nchildren; ++i)
      trie_print(&trie->children[i], level+1);
}

static
int
trie_cmp(const void *search,
         const void *element)
{
   const char *key = search;
   const struct trie *trie = element;
   char buf[sizeof(char*)] = {0};
   const char * prefix;
   if (trie)
      prefix = packedstring_robuf(&trie->prefix, buf);
   else
      prefix = buf;
   return key[0] > prefix[0] ? 1 : (key[0] == prefix[0] ? 0 : -1);
}

static
bool
trie_bsearch(const char *key,
             const struct trie *list,
             const size_t len,
             size_t * const index)
{
   struct trie *t = bsearch(key, list, len,
                            sizeof(struct trie),
                            trie_cmp);
   if (t && index)
      *index = t - list;
   return !!t;
}

bool
trie_insert(struct trie * const trie,
            const char * const name,
            void * const value)
{
   printf("inserted %s => %p\n", name, value);
   if (!value)
      return false;

   if (!name)
      return false;

   if (!trie->prefix)
   {
      printf("replaced root\n");
      packedstring_strncpytopackedstring(&trie->prefix, name, strlen(name)+1);
      trie->value = value;
      trie_print(trie, 0);
      return true;
   }

   struct trie *node = trie;

   for (const char *c = name; *c;)
   {
      char buf[sizeof(char*)];
      const char * const robuf = packedstring_robuf(&node->prefix, buf);
      const char *d = robuf;
      for (; *d && *c && *d == *c; ++d, ++c);
      if (*d) {
         // we didn't reach the end of node->prefix
         // we must split
         struct trie *newchild = trie_create();
         packedstring_strncpytopackedstring(&newchild->prefix, d, strlen(d)+1);
         newchild->value = node->value;
         newchild->nchildren = node->nchildren;
         newchild->children = node->children;

         size_t prefixlen = d-robuf;
         char nbuf[prefixlen+1];
         strncpy(nbuf, robuf, prefixlen);
         nbuf[prefixlen] = 0;
         packedstring_strncpytopackedstring(&node->prefix, nbuf, prefixlen+1);
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
         packedstring_strncpytopackedstring(&node->children[index].prefix, c, strlen(c)+1);
         node = &node->children[index];
         break;
      }
      node = &node->children[index];
   }

   node->value = value;

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
      if (node->prefix)
      {
         char buf[sizeof(char*)];
         const char *d = packedstring_robuf(&node->prefix, buf);
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
