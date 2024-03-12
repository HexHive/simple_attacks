#include <stdlib.h>

int global_array[16];

int main(int argc, char *argv[]) {
  int stack_array[16];
  int *ptr;

  switch(atoi(argv[1])) {
    default:
    case 0: ptr = &stack_array[0]; break;
    case 1: ptr = &global_array[0]; break;
    case 2: ptr = (int*)malloc(16*sizeof(int)); break;
    case 3: ptr = (int*)malloc(17*sizeof(int)); free(ptr); break;
  }

  // illegal read
  return ptr[16];
}

// clang -O1 -fsanitize=address -fno-common asan.c && ./a.out
