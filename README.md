# mymalloc
A implementation of a malloc and free in c 

## Authors
maf407 - Marco Ferreira
raj123 - Ryan Jones

QUESTIONS:
1. For this given heap, our malloc decided to allocate in this position instead of the first available. This is because we check to see if a new header can be created as well. Is this good design?

```c
PRINTING HEAP
Used: 0, Data Block: 152
Used: 1, Data Block: 88
Used: 1, Data Block: 152 <-
Used: 0, Data Block: 3696
0�aaaaaaaaaaa0`bbbbbbbbbbb1Xccccc1-�-�ddddddddddddddddddddddddddddddddddd0-�-p
END HEAP
```

2. sizeof(char) is 1 byte, however char literals are 4 bytes, how do we handle this with our malloc if someone tries the following:

```c
char *c = malloc(sizeof(char) * 20);

for (int i = 0; i < 20; i++){
    c[i] = 'a';
}
```

3. Can I use memcpy(heap.bytes, &header, sizeof(metadata)); to allocate my metadata on to the 'heap'