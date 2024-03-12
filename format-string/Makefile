PROGS=01-format_string-stack-EIP 02-format_string-stack-EIP-stack_protect 03-format_string-2ROP x64-format_string
.PHONY=all clean $(PROGS)

all: $(PROGS)

01-format_string-stack-EIP: format_string.c
	gcc -m32 -O0 -fno-stack-protector -DMAKEITEASY -Wall -Wextra -o $@ $<

02-format_string-stack-EIP-stack_protect: format_string.c
	gcc -m32 -O0  -DMAKEITEASY -Wall -Wextra -o $@ $<

03-format_string-2ROP: format_string.c
	gcc -m32 -O0 -Wall -Wextra -o $@ $<

x64-format_string: format_string.c
	gcc -O0 -DMAKEITEASY -Wall -Wextra -o $@ $<
	
clean:
	rm -f $(PROGS)
