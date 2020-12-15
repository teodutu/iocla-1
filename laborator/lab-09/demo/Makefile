# IOCLA 2020
# USO remembers

CC=gcc
CFLAGS=-m32 -masm=intel -std=gnu11

all: demo

demo:  demo.c
	$(CC) $(CFLAGS) -o $@ $^

asm: demo.c
	$(CC) $(CFLAGS) -S $^

clean:
	rm -f *.s demo
