#include "test_assert.h"
#define XORCIPHER_IMPLEMENTATION
#include "xorcipher.h"

#include <time.h>

void test_base64_1(unsigned char length)
  {
  unsigned char message[256];
  for (int i = 0; i < length; ++i)
    message[i] = (unsigned char)i;
  char* b64 = xorcipher_base64_encode(message, length);
  unsigned long le;
  unsigned char* orig = xorcipher_base64_decode(&le, b64);
  TEST_EQ_INT(length, le);
  for (int i = 0; i < le; ++i)
    {
    TEST_EQ_INT(i, orig[i]);
    }
  free(b64);
  free(orig);
  }

void test_base64_encoding()
  {

  for (int i = 1; i < 256; ++i)
  {
    test_base64_1(i);
  }
  
  }

int main(int argc, const char* argv[])
  {
  (void)argc;
  (void)argv;  
  InitTestEngine();
  clock_t start_t, end_t;
  start_t = clock();
  test_base64_encoding();
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
