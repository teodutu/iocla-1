CC=gcc
CFLAGS=-m32 -no-pie -fno-omit-frame-pointer -fno-stack-protector

all: demo_no-pie demo_no-pie_no-pic

demo_no-pie: demo.c
	$(CC) $(CFLAGS) $^ -o $@

demo_no-pie_no-pic: demo.c
	$(CC) $(CFLAGS) -fno-pic $^ -o $@

clean:
	rm -rf *.o demo_* payload .gdb_history
