# mymalloc
A implementation of a malloc and free in c 

## Authors
maf407 - Marco Ferreira
raj123 - Ryan Jones

### Memgrind Workloads

Our `Memgrind` consists of the three given workloads, as well as two of our own creation.

1. **Workload 1**: Fill the heap with 32-byte chunks, deallocate the last two 64 byte chunk, and try to allocate a -byte chunk. This tests that our coalescing mechanism works properly.
   
2. **Workload 2**: Allocate 30 chunks of random sizes between 1 and 64 bytes, then deallocate them in reverse order.

These two workloads are implemented in `test4.c` and `test6.c`. The entire workload in `memgrind` was run 50 times. Memgrind also tested the performance of our mymalloc. We then compared the results to the real malloc

### Feature Tests

We created more tests to ensure that our malloc function features worked correctly. The workloads in `memgrind` consist of `test1.c`, `test2.c`, `test3.c`, `test4.c`, and `test6.c`. Additionally, we have:

- **`test5.c`**: Chooses a number between 1 and 4 to perform a specific test to trigger an error:  
  - 1: Freeing an already deallocated pointer  
  - 2: Freeing a `NULL` pointer, which won’t work for our malloc and gives an appropriate message  
  - 3: Freeing an offset pointer  
  - 4: Double freeing a chunk
- **`test7.c`**: Allocates 10 long chunks, prints them out backwards, and then frees them.
- **`test8.c`**: Allocates memory for a long chunk (size of a long), then prints the address and byte size. Doesn't free, expect a leak statement
- **`test9.c`**: Attempts to allocate memory for a chunk with a negative size. This should fail.
- **`test10.c`**: Attempts to allocate memory for a chunk using arithmetic to determine the size. Then prints the address.

### Memgrind Runtime

We used `gettimeofday()` to measure the runtime of our `Memgrind`. Regular `malloc` varied slightly but averaged around **203 milliseconds**, while our custom `malloc` took around **413 milliseconds**. When averaging out those times we got a time of **6 milliseconds** per workload iteration with our 'malloc' versus **3 milliseconds** per iteration of regular 'malloc'.
