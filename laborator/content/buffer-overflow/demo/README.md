# Buffer Overflow - Writeup
## Description
We decompile the program in [Ghidra](https://github.com/NationalSecurityAgency/ghidra/) and notice the following:
1. It reads a string of 10 bytes, using `scanf`.
2. The buffer into which the input is read is placed on the stack.
Let's call it `buff`.
3. There is another variable in the `read_data` function, that is initialised with 2.
Let's call this variable `var`.
If its value is `0xcafebabe`, the string `"So far, so good!"` is printed.
4. There is an unused function, called `manele`.

### Input
This one is obvious: the program reads a string into a 10-byte stack buffer, using `scanf`.

### Vulnerabilities
There are no [stack canaries](https://www.sans.org/blog/stack-canaries-gingerly-sidestepping-the-cage/).
This is visible both by looking at the disassembled code and by looking at the `-fno-stack-protector` in the makefile.

`scanf` is vulnerable because it doesn't stop reading until it finds a space, or a `\n`.
Therefore, we can perform a buffer overflow attack to overwrite the contents of the stack, such as `var`, or the return address.


## The Attack
### Overwriting `var`
We use `objdump -M intel -d demo` to disassemble the binary.
From the snippet below, we see that `var` is placed at `ebp - 0xc` and `buff` is at `ebp - 0x16`. 
```asm
mov    DWORD PTR [ebp-0xc],0x2
sub    esp,0x8
lea    eax,[ebp-0x16]
push   eax
push   0x804a013
call   80490b0 <__isoc99_scanf@plt>
```
In order to overwrite `var`, we first need to reach it.
To do so, we must fill the contents of `buff` with random bytes.
We call those bytes _padding_.

Therefore, we need a padding of `0x16 - 0xc = 10` bytes.
Then, we need to provide the contents of `var`.
We want it to be `0xCAFEBABE`.

But, keep in mind that our CPUs' byte orders are **little endian**.
So we can't just write it simply as `"\xca\xfe\xba\xbe"`.
Instead, we need to write the bytes in reverse order: `"\xbe\xba\xfe\xce"`.

Putting it together so far, the payload looks like this:
```python
payload = "a" * 10 + "\xbe\xba\xfe\xce"
```

### "Calling" `manele`
We are now building on top of the attack above and are adding to that payload.

In order to execute code _of our choosing_, we need to overwrite a **code pointer** (return address, function pointer etc.).
The closest one to our input is the return address on the stack of `read_data`.

In order to overwrite said return address, we need to further pad the above `payload` until we reach the return address.
In the previous section, we saw that `var` is placed at `ebp-0xc`.
It's 4 bytes wide, so it ends `ebp-0x8`.
We know from [lab 9](https://ocw.cs.pub.ro/courses/iocla/laboratoare/laborator-09) that the return address is placed at `ebp+0x4`.
So the amount of padding we'll need is `0x8 + 0x4 = 12` bytes.
We will end up overwriting the old `ebp` as well, but we don't care.
This will result in a seg fault, but only **after** we're done with our exploit.

Now all we need is to provide the address of `manele`.
We find it using `nm`:
``` bash
$ nm demo | grep manele
080491d6 T manele
```

All in all, the complete payload for our attack is:
```python
payload = "a" * 10 + "\xbe\xba\xfe\xce" + "a" * 12 + "\xd6\x91\x04\x08"
```


## Further Work
### Pass the right argument to `manele`
If you have no life, you can try to "call" `manele` with the right argument so that the string `"OMG!"` is also printed.
Look at a typical stack frame and think how far apart should the address of `manele` and the argument be in your payload.
