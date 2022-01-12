NASM = nasm
AFILES = demo.asm
OBJS = $(AFILES:.asm=.o)
ASM_FLAGS = -f elf32 -g
LD=gcc
LDFLAGS = -m32 -g
BINARIES = demo

all : $(BINARIES)

%.o : %.asm
	$(NASM) $(ASM_FLAGS) -o $@ $<

mean: mean.o
	$(LD) $(LDFLAGS) -o $@ $^

clean:
	rm -f *.o $(BINARIES) *.s
	rm -f *~
