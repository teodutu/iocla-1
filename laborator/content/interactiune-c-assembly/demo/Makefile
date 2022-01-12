CC = gcc
CFLAGS = -m32 -fno-pic
LDFLAGS = -m32 -no-pie
TARGETS = demo_inline_func demo_inline_asm

all: $(TARGETS)

demo_inline_func.o: demo_inline_func.c
	$(CC) $(CFLAGS) -c $^

demo_inline_asm.o: demo_inline_asm.c
	$(CC) $(CFLAGS) -masm=intel -c $^ -o $@

clean:
	rm -f *.o $(TARGETS)

.PHONY: all clean
