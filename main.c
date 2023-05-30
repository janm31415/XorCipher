#define XORCIPHER_IMPLEMENTATION
#include "xorcipher.h"

#include <stdio.h>

int main(int argc, char** argv)
  {
  #if 0
  unsigned char message[256];
  for (int i = 0; i < 256; ++i)
    message[i] = (unsigned char)i;
    
  char* b64 = xorcipher_base64_encode(message, 256);
  
  printf("%s\n", b64);
  
  unsigned long le;
  unsigned char* orig = xorcipher_base64_decode(&le, b64);
  
  for (int i = 0; i < le; ++i)
    {
    int r = (int)orig[i];
    printf("%d\n", r);
    }
  
  free(b64);
  free(orig);
  #else
  
  char* m = "This is the original message\n!!!\n";
  const char* base64_password = "ADRASDjasdflkwef0681";
  char* message = malloc(strlen(m));
  for (int i = 0; i < strlen(m); ++i)
    message[i] = m[i];
  
  
  #if 1
  unsigned long l = strlen(message);
  xorcipher_xor((unsigned char*)message, l, base64_password);
  for (int i = 0; i < l; ++i)
    printf("%c", message[i]);
  xorcipher_xor((unsigned char*)message, l, base64_password);
  for (int i = 0; i < l; ++i)
    printf("%c", message[i]);
  #else
  
  unsigned long le;
  unsigned char* orig = xorcipher_base64_decode(&le, base64_password);
  char* b64 = xorcipher_base64_encode(orig, le);
  printf("%s", b64);
  free(orig);
  free(b64);
  
  #endif
  
  free(message);
  #endif
  return 0;
  }
