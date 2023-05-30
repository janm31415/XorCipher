#define XORCIPHER_IMPLEMENTATION
#include "xorcipher.h"

#include <stdio.h>
#include <string.h>

int main(int argc, char** argv)
  {
  
  unsigned char message[256];
  for (int i = 0; i < 256; ++i)
    message[i] = (unsigned char)i;
    
  char* b64 = xorcipher_base64_encode(message, 256);
  
  printf("%s\n", b64);
  
  unsigned long le;
  unsigned char* orig = xorcipher_base64_decode(&le, b64, strlen(b64));
  
  for (int i = 0; i < le; ++i)
    {
    int r = (int)orig[i];
    printf("%d\n", r);
    }
  
  free(b64);
  free(orig);
  
  return 0;
  }
