#define XORCIPHER_IMPLEMENTATION
#include "xorcipher.h"

#include <stdio.h>

static long filesize(FILE* fp)
  {
	fseek(fp, 0L, SEEK_END);
	long sz = ftell(fp);
	fseek(fp, 0L, SEEK_SET);
	return sz;
  }

int main(int argc, char** argv)
  {
  if (argc < 3)
    {
    printf("Usage: XorCipher b64 file\n");
    printf(" with b64  : base64 encoded cipher\n");
    printf("      file : file to encode/decode\n");
    return 0;
    }
  else
    {
    FILE* file=fopen(argv[2], "rb");
    if(!file)
      {
      printf("I cannot open %s\n", argv[2]);
      return -1;
      }
    unsigned char* cipher;
    unsigned long cipher_size;
    FILE* cipher_file = fopen(argv[1], "r");
    if (!cipher_file)
      {
      cipher = xorcipher_base64_decode(&cipher_size, argv[1]);
      }
    else
      {
      long cipher_file_size = filesize(cipher_file);
      char* cipher_file_buffer = malloc(cipher_file_size);
      if (fread(&cipher_file_buffer, sizeof(unsigned char), cipher_file_size, cipher_file) != cipher_file_size)
        {
        printf("I could not read the cipher file %s\n", argv[1]);
        free(cipher_file_buffer);
        fclose(file);
        fclose(cipher_file);
        return -1;
        }
      fclose(cipher_file);
      cipher = xorcipher_base64_decode(&cipher_size, cipher_file_buffer);
      free(cipher_file_buffer);
      }
    long file_size = filesize(file);
    for (long i = 0; i < file_size; ++i)
      {
      int c = fgetc(file);
      int x = cipher[i%cipher_size];
      printf("%c",c^x);
      }
    free(cipher);
    fclose(file);
    }
  return 0;
  }
