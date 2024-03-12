#include <pthread.h>

int global;

void *thread1(void *x) {
  global = 42;
  return x;
}

int main(int argc, char *argv[]) {
  pthread_t t;
  pthread_create(&t, NULL, thread1, NULL);

  global = 23;

  pthread_join(t, NULL);
  return global;
}
// clang -fsanitize=thread -O1 tsan.c
