#include "test_assert.h"
#define XORCIPHER_IMPLEMENTATION
#include "xorcipher.h"

#include <time.h>
#include <stdint.h>

void test_base64_1(unsigned char length)
{
  unsigned char message[256];
  for (int i = 0; i < length; ++i)
    message[i] = (unsigned char)i;
  char* b64 = xorcipher_base64_encode(message, length);
  unsigned long le;
  unsigned char* orig = xorcipher_base64_decode(&le, b64);
  TEST_EQ_INT(length, le);
  for (unsigned long i = 0; i < le; ++i)
  {
    TEST_EQ_INT(i, orig[i]);
  }
  free(b64);
  free(orig);
}

void test_base64_2(unsigned char length)
{
  unsigned char message[256];
  unsigned int seed = 7651351;
  for (int i = 0; i < length; ++i)
    {
    message[i] = (unsigned char)(seed&255);
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);
    }
  char* b64 = xorcipher_base64_encode(message, length);
  unsigned long le;
  unsigned char* orig = xorcipher_base64_decode(&le, b64);
  TEST_EQ_INT(length, le);
  seed = 7651351;
  for (unsigned long i = 0; i < le; ++i)
  {
    TEST_EQ_INT(seed&255, orig[i]);
    seed ^= (seed << 13);
    seed ^= (seed >> 17);
    seed ^= (seed << 5);
  }
  free(b64);
  free(orig);
}

void test_base64_encoding()
{
  for (int i = 1; i < 256; ++i)
  {
    test_base64_1((unsigned char)i);
    test_base64_2((unsigned char)i);
  }
}

void test_xor_cipher_message(const char* message, const char* base64_password)
{
  unsigned long le = (unsigned long)strlen(message);
  unsigned char* m = (unsigned char*)malloc(le);
  for (unsigned long i = 0; i < le; ++i)
    m[i] = message[i];
  xorcipher_xor(m, le, base64_password);
  xorcipher_xor(m, le, base64_password);
  for (unsigned long i = 0; i < le; ++i)
    {
    TEST_EQ_INT(m[i], message[i]);
    }
  free(m);
}

void test_xor()
{
  test_xor_cipher_message("Hello world!!!\n", "ADRASDjasdflkwef0681");
  test_xor_cipher_message("Hello world!!!\n\r..!!!@!#$%^%^&*())__", "ADRAsdflkjqelkvcjflkjaweff////*****ASDFASDF31310684035840SDjasdflkwef0681");
}

int main(int argc, const char* argv[])
{
  (void)argc;
  (void)argv;
  InitTestEngine();
  clock_t start_t, end_t;
  start_t = clock();
  test_base64_encoding();
  test_xor();
  end_t = clock();
  double total_t = (double)(end_t - start_t) / CLOCKS_PER_SEC;
  if (!testing_fails)
  {
    TEST_OUTPUT_LINE("Succes: %d tests passed.", testing_success);
  }
  else
  {
    TEST_OUTPUT_LINE("FAILURE: %d out of %d tests failed (%d failures).", testing_fails, testing_success + testing_fails, testing_fails);
  }
  TEST_OUTPUT_LINE("Test time: %f seconds.", total_t);
  return CloseTestEngine(1);
}
