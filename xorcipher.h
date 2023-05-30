#ifndef XORCIPHER_INCLUDE_H
#define XORCIPHER_INCLUDE_H
/*
 Do this:
 #define XORCIPHER_IMPLEMENTATION
 before you include this file in *one* C or C++ file to create the implementation.
 
 // i.e. it should look like this:
 #include ...
 #include ...
 #include ...
 #define XORCIPHER_IMPLEMENTATION
 #include "xorcipher.h"
 */

#include <stdlib.h>
#include <string.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef XORCIPHER_DEF
#ifdef XORCIPHER_STATIC
#define XORCIPHER_DEF static
#else
#define XORCIPHER_DEF extern
#endif
#endif

XORCIPHER_DEF char* xorcipher_base64_encode(const unsigned char* bytes, unsigned long length);
XORCIPHER_DEF unsigned char* xorcipher_base64_decode(unsigned long* decoded_size, const char* encoded_string);
XORCIPHER_DEF void xorcipher_xor(unsigned char* message, unsigned long message_length, const char* base64_password);

#ifdef __cplusplus
}
#endif

#endif //XORCIPHER_INCLUDE_H

#ifdef XORCIPHER_IMPLEMENTATION

#ifndef XORCIPHER_MALLOC
#  define XORCIPHER_MALLOC(x) malloc(x)
#endif

#ifndef XORCIPHER_FREE
#  define XORCIPHER_FREE(x) free(x)
#endif

#ifndef XORCIPHER_REALLOC
#  define XORCIPHER_REALLOC(x, size) realloc(x, size)
#endif

static const char base64_chars[64] =
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"0123456789+/";


XORCIPHER_DEF char* xorcipher_base64_encode(const unsigned char* bytes, unsigned long length)
{
  char buffer[3];
  char* result = XORCIPHER_MALLOC(length * 4 / 3 + 4);
  int count = 0;
  unsigned long j = 0;
  for (unsigned long i = 0; i < length; ++i)
  {
    buffer[count++] = bytes[i];
    if (count == 3)
    {
      result[j++] = base64_chars[(buffer[0] & 0xfc) >> 2];
      result[j++] = base64_chars[((buffer[0] & 0x03) << 4) + ((buffer[1] & 0xf0) >> 4)];
      result[j++] = base64_chars[((buffer[1] & 0x0f) << 2) + ((buffer[2] & 0xc0) >> 6)];
      result[j++] = base64_chars[buffer[2] & 0x3f];
      count = 0;
    }
  }
  
  if(count > 0)
  {
    for (int k = count; k < 3; ++k)
      buffer[k] = 0;
    result[j] = base64_chars[(buffer[0] & 0xfc) >> 2];
    result[j+1] = base64_chars[((buffer[0] & 0x03) << 4) + ((buffer[1] & 0xf0) >> 4)];
    result[j+2] = base64_chars[((buffer[1] & 0x0f) << 2) + ((buffer[2] & 0xc0) >> 6)];
    result[j+3] = base64_chars[buffer[2] & 0x3f];
    j += count;
    while (j++ < 3)
      result[j] = '=';
  }
  result[j] = '\0';
  return result;
}

static int is_base64(const char ch)
{
  for (int k = 0; k < 64; ++k)
  {
    if (ch == base64_chars[k])
      return k;
  }
  return -1;
}

XORCIPHER_DEF unsigned char* xorcipher_base64_decode(unsigned long* decoded_size, const char* encoded_string)
{
  unsigned long encoded_string_length = strlen(encoded_string);
  unsigned char char_array_4[4];
  unsigned char char_array_3[3];
  unsigned char* result = (unsigned char*)XORCIPHER_MALLOC(encoded_string_length * 3 / 4);
  int i = 0;
  unsigned long j = 0;
  int in_ = 0;
  int k;
  
  while (encoded_string_length-- && (encoded_string[in_] != '=') && (k=is_base64(encoded_string[in_]))>=0)
  {
    char_array_4[i++] = (unsigned char)k;
    ++in_;
    if (i == 4)
    {
      result[j++] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      result[j++] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      result[j++] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
      i = 0;
    }
  }
  
  if (decoded_size != NULL)
      *decoded_size = i + j;
  
  if (i) {
    for (int q = i; q < 4; ++q)
      char_array_4[q] = 0;
    if (decoded_size != NULL)
      *decoded_size = i + j - 1;
      
    result[j++] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    result[j++] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    result[j++] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];
    
  }
  
  return result;
}

XORCIPHER_DEF void xorcipher_xor(unsigned char* message, unsigned long message_length, const char* base64_password)
{
  unsigned long decoded_size;
  unsigned char* pw = xorcipher_base64_decode(&decoded_size, base64_password);
  //for (unsigned long i = 0; i < message_length; ++i)
  //  {
  //  message[i] ^= pw[i % decoded_size];
  //  }
  XORCIPHER_FREE(pw);
}

#endif // XORCIPHER_IMPLEMENTATION
