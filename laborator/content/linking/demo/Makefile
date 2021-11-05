CC = gcc
CFLAGS = -m32 -fPIC
LDFLAGS = -m32 -no-pie
LDFLAGS_STATIC = $(LDFLAGS) -static


all: prog_dyn prog_static prog_lib_dyn prog_lib_static


prog_dyn: main.o arr_sum.o print.o
# $(CC) $(LDFLAGS) $^ -o $@
	ld -m elf_i386 -L/usr/lib/gcc/x86_64-linux-gnu/9/32/ /usr/lib32/crt1.o /usr/lib32/crti.o /usr/lib32/crtn.o $^ -o $@  --start-group -lc -lgcc -lgcc_eh --end-group


prog_static: main.o arr_sum.o print.o
# $(CC) $(LDFLAGS_STATIC) $^ -o $@
	ld -static -m elf_i386 -L/usr/lib/gcc/x86_64-linux-gnu/9/32/ /usr/lib32/crt1.o /usr/lib32/crti.o /usr/lib32/crtn.o $^ -o $@  --start-group -lc -lgcc -lgcc_eh --end-group


prog_lib_dyn: main.o libutils.so
	$(CC) $(LDFLAGS) $< -o $@ -lutils -L.

libutils.so: arr_sum.o print.o
	$(CC) $(LDFLAGS) -shared $^ -o $@


# Doar biblioteca e statica
# Linkarea e dinamica (libutils.a e ca un fisier obiect)
prog_lib_static: main.o libutils.a
	$(CC) $(LDFLAGS) $< -o $@ -lutils -L.

libutils.a: arr_sum.o print.o
	ar rc $@ $^


clean:
	rm -f *.o *.a *.so prog_* 


.PHONY: all clean run
