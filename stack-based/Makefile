BINS=stack stack-ci-wrapper
all: $(BINS)

stack: stack.c
	gcc -g -fno-stack-protector -z execstack stack.c -o stack

stack-ci-wrapper: stack-ci-wrapper.c
	gcc -g -std=c99 stack-ci-wrapper.c -o stack-ci-wrapper

clean:
	rm -f $(BINS)

