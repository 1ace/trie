#include "packedstring.h"

#include <string.h>

struct packedstring*
packedstring_create()
{
   return NULL;
}

bool
packedstring_ispacked(struct packedstring * const * const packedstring)
{
   return *packedstring == NULL || (size_t)*packedstring & 1;
}

struct packedstring*
packedstring_strncpytopackedstring(struct packedstring * * const dst, const char * const src, const size_t size)
{
   if (!packedstring_ispacked(dst))
      free(*dst);
   *dst = NULL;

   // Strings strictly shorter than sizeof(char *) can be packed
   // but strings of exactly sizeof(char *), where the last byte is nul,
   // can also  be stored. E.g. assuming sizeof(char *) = 8:
   // 0 1 2 3 4 5 6 7
   // a b c d e f g     // ok
   // a b c d e f g h   // no
   // a b c d e f g \0  // ok
   if (size < sizeof(char *) || (size == sizeof(char *) && src[sizeof(char *)-1] == 0))
   {
      size_t *pdst = (size_t *)dst;
      unsigned char i = 0;
      for (; src[i] && i < size; ++i)
      {
         (*pdst) |= (size_t)src[i] << (i + 1)*8;
      }
      (*pdst) |= (i << 4) | 1;
   }
   else
   {
      posix_memalign((void**)dst, sizeof(void*), size);
      strncpy((char*)*dst, src, size);
   }
   return *dst;
}

char*
packedstring_strncpyfrompackedstring(char *dst, struct packedstring * const * const src, const size_t size)
{
   if (packedstring_ispacked(src))
   {
      size_t len = packedstring_strlen(src);
      unsigned char i = 0;
      for (; i < len && i < size; ++i)
         dst[i] = (*(size_t *)src) >> (i + 1)*8;
      if (i < size)
         dst[i] = 0;
      return dst;
   }
   return strncpy(dst, (char*)*src, size);
}

const
char * const
packedstring_robuf(struct packedstring * const * const packedstring, char buf[sizeof(char*)])
{
   if (packedstring_ispacked(packedstring))
      return packedstring_strncpyfrompackedstring(buf, packedstring, sizeof(char*));
   return (char *)packedstring;
}

size_t
packedstring_strlen(struct packedstring * const * const packedstring)
{
   if (packedstring_ispacked(packedstring))
      return *((size_t *)packedstring) >> 4 & 0xf;
   return strlen((char *)*packedstring);
}

void
packedstring_destroy(struct packedstring * * const packedstring)
{
   if (!((size_t)*packedstring & 1))
      free(*packedstring);
   *packedstring = NULL;
}



