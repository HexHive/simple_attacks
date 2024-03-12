#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  char authorized = 0;
  char cookie[31];
  if (getenv("AUTH") != NULL && strcmp(getenv("AUTH"), "MAGIC") == 0) authorized = 1;
  printf("Give me a cookie (%p, %p)\n", cookie, getenv("EGG"));
  strcpy(cookie, argv[1]);
  printf("Thanks for the %s\n", cookie);
  if (authorized) {
    printf("Congratulations, you are authorized!\n");
  }
  return 0;
}

/*
Run w/o ASLR:
setarch `arch` -R ./stack-codeinject
./stack cookie
AUTH=MAGIC ./stack
./stack cookie
./stack cookies_are_delicious_and_tasty.
*/
