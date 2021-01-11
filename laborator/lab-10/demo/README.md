# Laborator 10 - Explicatii
Am compilat demo-ul cu urmatoarele flaguri, pentru a fi mai facil atacul pe
care intentionam sa-l facem:
```
-no-pie
-fno-omit-frame-pointer
-fno-stack-protector
```
Optional, se pot adauga si flagurile `-fno-pie`/`-fno-pic`.


## Scop
Programul `demo` afiseaza `"RIP Dani Mocanu!"`, dupa care citeste un string si
se termina. Inspectandu-l cu `ghidra`/`objdump`, observam 3 aspecte:
1. Citirea stringului se face in functia `read_data()`, prin `scanf()`, care
citeste caractere pana la spatiu sau `\n`, deci poate teoretic sa citeasca
oricate caractere, ceea ce reprezinta o **vulnerabilitate**.
2. Bufferul in care se citeste stringul este pe **stiva**, deci daca am scrie in
el mai multe date decat capacitatea sa, am putea suprascrie `EIP`-ului
functiei apelante, iar cand se va executa `ret`, se va executa cod de la adresa
suprascrisa de noi.
3. Exista o functie neapelata, `rip_dani_mocanu()` pe care, in onoarea legendei
manelelor autohtone, trebuie s-o apelam cumva.

Deci vrem sa facem un *buffer overflow* in stringul de pe stiva functiei
`read_data()`, prin care sa suprascriem `EIP`-ul salvat, astfel incat, dupa ce
se incheie `read_data()`, executia sa continue de la inceputul functiei
`rip_dani_mocanu()`.


## Strategie
Ca sa efectuam atacul propriu-zis trebuie sa stim doua lucruri.

Primul e offsetul fata de `EBP` la care a plasat compilatorul stringul in care
se face citirea cu `scanf()`. Folsind `objdump`, vedem instructiunile:
```
lea    eax,[ebp-0x2c]
push   eax
push   0x804a06a
call   8049090 <__isoc99_scanf@plt>
```
Din ele deducem ca stringul incepe de la `EBP - 0x2c`.

Apoi, avem nevoie sa stim unde e `EIP`-ul pe stiva. Din
[laboratorul 7](https://ocw.cs.pub.ro/courses/iocla/laboratoare/laborator-07)
stim ca `EIP`-ul e pus la `EBP + 4`. Vedeti si imaginea de mai jos.
![](https://ocw.cs.pub.ro/courses/_media/iocla/laboratoare/function_stack1.jpg?cache=)

Acum stim tot ce avem neovie ca sa cream atacul. El consta in formarea unui
**payload**, adica a unui string pe care il va citi programul `demo`. Payloadul
trebuie sa contina un **padding** (caractere de umplutura) cu lungimea de
`0x2c + 4` caractere, cu care sa "umplem" stiva de unde citeste `scanf()`-ul si
pana la `EIP`-ul pe care vrem sa-l suprascriem, urmat de adresa de la care vrem
sa se execute codul. Adresa asta o luam tot din output-ul `objdumpului`, si
anume `0x080491b6`.

Cel mai simplu mod sa cream un astfel de string e in *Python*:
```
python -c 'print "a" * (0x2c + 4) + "\xb6\x91\x04\x08"' | ./demo_no-pie_no-pic
```
Payloadul e format din 48 (`0x2c + 4`) de caractere `"a"` (paddingul), urmate
de adresa functiei `rip_dani_mocanu()` **scrisa little endian**.


## Parametrii de compilare
Sa explicam parametrii cu care am compilat codul. Incercati sa compilati si fara
ei si observati cum se schimba outputul din `objdump`.

### -fno-omit-frame-pointer
Din cand in cand, pentru functii scurte, compilatorul decide sa nu mai creeze
un cadru de stiva nou si nu mai adauga secventele de mai jos:
```
push ebp
mov ebp, esp
...
mov esp, ebp
pop ebp
```
Pentru atacul pe care vrem sa-l facem, avem nevoie de crearea unui cadru de
stiva pentru functia `read_data()` si de aici nevoia de flagul asta.

### fno-stack-protector
Pentru a proteja programul de atacuri de tip *buffer overflow*, compilatorul
adauga pe stiva, intre variabilele locale si `EBP`-ul functiei apelante ceea ce
se cheama
[stack canaries](https://en.wikipedia.org/wiki/Buffer_overflow_protection#Canaries).
Ele sunt cel mai adesea niste valori generate aleator la runtime. Practic, se
generaza **o singura valoare** pentru fieacre proces, care este scrisa pe stiva
tuturor functiilor acelui proces. La finalul functiei, inainte de `leave; ret`,
se verifica daca valoarea de pe stiva este egala cu cea generata initial. In caz
contrar, executia se inchide imediat si sa afiseaza:
```
*** stack smashing detected ***: <fisier_executabil> terminated
Aborted (core dumped)
```
Deci *stack canaries* previn suprascrierea prin *buffer overflow* a valorilor
`EBP`-ului si `EIP`-ului apelantului.

### -no-pie
Un executabil **independent de pozitie (PIE)** inseamna ca adresele
instructiunilor (vizibile cu `objdump`) sunt *relative*, niste offseturi fata de
inceputul zonei `.text`. La rulare, loaderul va incarca instructiunile din zona
`.text` de la o anumita adresa (aleatoare sau nu; depinde daca
[ASLR-ul](https://www.networkworld.com/article/3331199/what-does-aslr-do-for-linux.html)
e activat), la care adauga offseturile afisate de `objdump`.

Deci cand avem cod *PIE*, nu putem specifica o adresa ca atare din zona `.text`
intr-un payload.

### -fno-pic / -fno-pie
**Atentie!** Difera de `-no-pie` prin faptul ca aceste flaguri actioneaza asupra
codului, si nu a executabilului. Practic, `-fno-pic` si `-fno-pie` sunt flaguri
pentru compilatorul inclus in *GCC*, iar `-no-pie` este pentru linkerul care
genereaza executabilu efectiv. `-fno-pic` si `-fno-pie` fac ca datele din zone
precum `.data` si `.bss` sa fie accesate relativ la `EIP`, si nu prin adresa
propriu-zisa.

In general, aceste doua flaguri au efecte foarte similare, dar `-fno-pic` este
destinat bibliotecilor dinamice, iar `-fno-pie` fisierelor executabile. De
altfel, si eu am folosit `-fno-pic` in `Makefile`.

Accesarea `EIP`-ului se face prin constructii precum `__x86.get_pc_thunk.bx`,
al caror cod il putem vedea tot cu `objdump`. Constructia are rolul de a salva
`EIP`-ul in `EBX`, iar codul sau este urmatorul:
```
mov    ebx,DWORD PTR [esp]
ret
 ```
Incercati sa intelegeti cum functioneaza! Va ajuta sa intelegeti mai bine ce
contine un stack frame.
