#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <crypt.h>
#include <math.h>
#include <omp.h>


// Without newline
const int HASH_LEN = 86;
const int SALT_LEN = 19;
const int NUM_SYMBOLS = 93;
const int MAX_PASS_LEN = 5;

void int2pass(int i, int word_len, char* symbols, char* result) {
  int j;
  int indx;
  for(j=0; j<word_len; j++) {
    indx = ((int) floor(i/pow(NUM_SYMBOLS, word_len-j-1))) % NUM_SYMBOLS;
    result[j] = symbols[indx];
  }
  result[j+1] = '\0';
}

int main(int argc, char*argv[]) {
  struct crypt_data data;

  char symbols[NUM_SYMBOLS+1];
  char shadow[HASH_LEN+SALT_LEN+2];
  char salt[SALT_LEN+1];
  char pass[MAX_PASS_LEN+1];
  char givenPass[MAX_PASS_LEN+1];
  char hash[HASH_LEN+1];
  char givenHash[HASH_LEN+1];
  char *result;
  int len;
  int i, k;
  int nWords;
  int found;
  int wordsPerCheck;
  int loopsPerCheck;
  int numThreads;
  int wordsPerThread;
  int wordsPerLoop;
  int wordsThisLoop;
  int extraWords;
  int firstThisLoop;
  int lastThisLoop;

  wordsPerThread = 1000;
  wordsPerCheck = 20000;

  strcpy(symbols, "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789 !\"#$%&'()*+,-./:;<=>?@[]^_{|}~");

  if(argc < 2) {
    printf("Need to supply hash.\n");
    return 1;
  }
  else if(argc > 3) {
    printf("Too many arguments.\n");
  }

  if(argc == 3)
    numThreads = atoi(argv[2]);
  else
    numThreads = omp_get_max_threads();

  printf("Using %d threads.\n", numThreads);

  strcpy(shadow, argv[1]);
  strncpy(salt, shadow, SALT_LEN);
  salt[SALT_LEN] = '\0';
  strncpy(givenHash, shadow+SALT_LEN+1, HASH_LEN);
  givenHash[SALT_LEN+HASH_LEN+1] = '\0';

  printf("salt: '%s'\n", salt);
  printf("givenHash: '%s'\n", givenHash);

  data.initialized = 0;

  printf("Searching...\n");
  found = 0;
  for(len = 0; len <= MAX_PASS_LEN; len++) {
    nWords = pow(NUM_SYMBOLS, len);
    printf("len=%d, nWords = %d\n", len, nWords);
    loopsPerCheck = (int) ceil((float) nWords / (wordsPerCheck*numThreads));
    wordsPerLoop = nWords / loopsPerCheck;
    extraWords = nWords % wordsPerLoop;

    for(k=0; k<loopsPerCheck; k++) {
      printf("batch %d/%d\n", k+1, loopsPerCheck);
      if(k == loopsPerCheck-1 && extraWords != 0)
        wordsThisLoop = extraWords;
      else
        wordsThisLoop = wordsPerLoop;

      firstThisLoop = k * wordsPerLoop;
      lastThisLoop = firstThisLoop + wordsThisLoop;

      #pragma omp parallel for \
        private(i, pass, result, hash) \
        shared(found) \
        schedule(dynamic, wordsPerThread) \
        num_threads(numThreads)
      for(i=firstThisLoop; i<lastThisLoop; i++) {
        if(!found) {
          int2pass(i, len, symbols, pass);
          result = crypt_r(pass, salt, &data);
          strncpy(hash, result+SALT_LEN+1, HASH_LEN);
          if(!strcmp(hash, givenHash)) {
            found = 1;
            strcpy(givenPass, pass);
          }
        }
      }
      if(found)
        break;
    }
    if(found)
      break;
  }

  if(found)
    printf("Password is '%s'\n", givenPass);
  else
    printf("Password not found.");
}
