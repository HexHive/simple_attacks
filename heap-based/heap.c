#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct data {
  char buf[32];
  void (*fct)(int);
} *ptr;

int main(int argc, char* argv[]) {
  ptr = (struct data*)malloc(sizeof(struct data));
  ptr->fct = &exit;
  printf("Give me a cookie (%p %p)\n", ptr, getenv("EGG"));
  if (argc == 2) strcpy(ptr->buf, argv[1]);
  printf("Thanks for the %s\n", ptr->buf);
  ptr->fct(0);
  return 0;
}

/*
Run w/o ASLR:
setarch `arch` -R ./heap cookie
*/
