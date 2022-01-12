# IOCLA 2020
# USO remembers

CC=gcc
CFLAGS=-m32 -masm=intel
all: demo

demo:  demo.c
	$(CC) $(CFLAGS) -o $@ $^

asm: demo.c
	$(CC) $(CFLAGS) -S $^

clean:
	rm -f *.s demo
