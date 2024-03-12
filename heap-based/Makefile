BINS=heap heap-ci-wrapper
all: $(BINS)

heap: heap.c
	gcc -g -fno-stack-protector -z execstack heap.c -o heap

heap-ci-wrapper: heap-ci-wrapper.c
	gcc -g -std=c99 heap-ci-wrapper.c -o heap-ci-wrapper

clean:
	rm -f $(BINS)

