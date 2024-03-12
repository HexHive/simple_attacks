CFLAGS=-O3 -W -Wall -Wpedantic -Wextra
CC=clang++
HT=/home/gannimo/repos/Typesafety-IPC/LLVM/build/bin

all: base safe downcasts

base: typeconfusion.cc
	$(CC) $(CFLAGS) typeconfusion.cc -o typeconfusion

safe: typeconfusion.cc
	$(HT)/$(CC) $(CFLAGS) typeconfusion.cc -o typeconfusion-ht -fsanitize=ipcsan

downcasts: downcasts.cc
	$(CC) $(CFLAGS) downcasts.cc -o downcasts

clean:
	rm -f typeconfusion typeconfusion-ht downcasts
