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


 

### Memgrind Workloads

Our `Memgrind` consists of the three given workloads, as well as two of our own creation.

1. **Workload 1**: Fill the heap with 64-byte chunks until there is no space left, deallocate the last two chunks, and try to allocate a 128-byte chunk. This tests that our coalescing mechanism works properly.
   
2. **Workload 2**: Allocate 30 chunks of random sizes between 1 and 64 bytes, then deallocate them in reverse order.

These two workloads are implemented in `test4.c` and `test6.c`. The entire workload in `memgrind` was run 50 times.

### Additional Tests

We created more tests to ensure that our malloc function worked correctly. The workloads in `memgrind` consist of `test1.c`, `test2.c`, `test3.c`, `test4.c`, and `test6.c`. Additionally, we have:

- **`test5.c`**: Chooses a number between 1 and 4 to perform a specific test to trigger an error:  
  - 1: Freeing an already deallocated pointer  
  - 2: Freeing a `NULL` pointer, which won’t work for our malloc and gives an appropriate message  
  - 3: Freeing an offset pointer  
  - 4: Double freeing a chunk
- **`test7.c`**: Allocates 10 long chunks, prints them out backwards, and then frees them.
- **`test8.c`**: Allocates memory for a long chunk (size of a long), then prints the address and byte size. Doesn't free, expect a leak statement
- **`test9.c`**: Attempts to allocate memory for a chunk with a negative size. This should fail.

### Memgrind Runtime

We used `gettimeofday()` to measure the runtime of our `Memgrind`. Regular `malloc` varied slightly but averaged around **203 milliseconds**, while our custom `malloc` took around **413 milliseconds**.
