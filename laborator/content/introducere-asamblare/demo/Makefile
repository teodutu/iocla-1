NASM = nasm
ASM_FLAGS = -f elf32  # -g -F dwarf
LD = gcc
LDFLAGS = -m32 -g -fno-pie -no-pie

all : demo

demo: demo.o
	$(LD) $(LDFLAGS) $^ -o $@

demo.o : demo.asm
	$(NASM) $(ASM_FLAGS) $^ -o $@

run: demo
	./$<

clean:
	rm -f *.o demo

.PHONY: all clean
