#include "trie.h"
#include <stdio.h>

int main(void)
{
   struct trie *trie = trie_create();

   if (!trie_insert(trie, "foo", (void*)1))
      printf("failed to insert foo\n");

   if (!trie_insert(trie, "fooo", (void*)42))
      printf("failed to insert fooo\n");

   if (!trie_insert(trie, "bar", (void*)2))
      printf("failed to insert bar\n");

   if (!trie_insert(trie, "foo", (void*)3))
      printf("failed to insert foo again\n");

   if (!trie_insert(trie, "fof", (void*)4))
      printf("failed to insert fof\n");

   long foo, fooo, fof, bar, bab, empty, null;

   if (trie_fetch(trie, "foo", (void*)&foo))
      printf("foo = %ld\n", foo);
   else
      printf("foo not found\n");

   if (trie_fetch(trie, "fooo", (void*)&fooo))
      printf("fooo = %ld\n", fooo);
   else
      printf("fooo not found\n");

   if (trie_fetch(trie, "bar", (void*)&bar))
      printf("bar = %ld\n", bar);
   else
      printf("bar not found\n");

   if (trie_fetch(trie, "fof", (void*)&fof))
      printf("fof = %ld\n", fof);
   else
      printf("fof not found\n");

   if (trie_fetch(trie, "bab", (void*)&bab))
      printf("bab = %ld\n", bab);
   else
      printf("bab not found\n");

   if (trie_fetch(trie, "", (void*)&empty))
      printf("empty = %ld\n", empty);
   else
      printf("empty not found\n");

   if (trie_fetch(trie, NULL, (void*)&null))
      printf("NULL key = %ld\n", null);
   else
      printf("NULL key not found\n");

   if (trie_fetch(trie, "foo", NULL))
      printf("NULL value found\n");
   else
      printf("NULL value not found\n");

   trie_destroy(trie);

   return 0;
}
