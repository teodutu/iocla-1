.PHONY: all clean run build

all: checker

build: checker

run: checker
	./checker

caesar.o: $(SKEL_FOLDER)caesar.asm
	nasm -f elf $^ -o $@

otp.o: $(SKEL_FOLDER)otp.asm
	nasm -f elf $^ -o $@

vigenere.o: $(SKEL_FOLDER)vigenere.asm
	nasm -f elf $^ -o $@

bin_to_hex.o: $(SKEL_FOLDER)bin_to_hex.asm
	nasm -f elf $^ -o $@

my_strstr.o: $(SKEL_FOLDER)my_strstr.asm
	nasm -f elf $^ -o $@

checker.o: checker.c
	gcc -c -g -m32 $^ -o $@

checker: checker.o caesar.o otp.o vigenere.o bin_to_hex.o my_strstr.o
	gcc -m32 -g $^ -o $@
	rm *.o

clean:
	rm checker
	rm output/*