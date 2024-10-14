# mymalloc
A implementation of a malloc and free in c 

## Authors
Marco Ferreira
Ryan Jones

### Memgrind Workloads

Our `Memgrind` consists of the three given workloads, as well as two of our own creation.

1. **Workload 1**: malloc() and immediately free() a 1-byte object, 120 times.

2. **Workload 2**: Use malloc() to get 120 1-byte objects, storing the pointers in an array, then use free() to deallocate the chunks.

3. **Workload 3**: Create an array of 120 pointers. Repeatedly make a random choice between allocating a 1-byte object and adding the pointer to the array and deallocating a previously allocated object (if any), until you have allocated 120 times. Deallocate any remaining objects.

4. **Workload 4**: Fill the heap with 32-byte chunks, deallocate the last two 64 byte chunk, and try to allocate a 128-byte chunk. This tests that our coalescing mechanism works properly.
   
5. **Workload 5**: Allocate 30 chunks of random sizes between 1 and 64 bytes, then deallocate them in reverse order.

These two workloads are implemented in `test4.c` and `test6.c`. The entire workload in `memgrind` was run 50 times. Memgrind also tested the performance of our mymalloc. We then compared the results to the real malloc

### Feature Tests

We created more tests to ensure that our malloc function features worked correctly. The workloads in `memgrind` consist of `test1.c`, `test2.c`, `test3.c`, `test4.c`, and `test6.c`. Additionally, we have:

- **`test5.c`**: Chooses a number between 1 and 4 to perform a specific test to trigger an error and/or crash:  
  - 1: Freeing an already deallocated pointer  
  - 2: Freeing a `NULL` pointer, which won’t work for our malloc and gives an appropriate message  
  - 3: Freeing an offset pointer  
  - 4: Double freeing a chunk
- **`test7.c`**: Allocates 10 long chunks, prints them out backwards, and then frees them.
- **`test8.c`**: Allocates memory for a long chunk (size of a long), then prints the address and byte size. Doesn't free, expect a leak statement
- **`test9.c`**: Attempts to allocate memory for a chunk with a negative size. **This should fail.**
- **`test10.c`**: Attempts to allocate memory for a chunk using arithmetic to determine the size. Then prints the address.

### Memgrind Runtime

We used `gettimeofday()` to measure the runtime of our `Memgrind`. Regular `malloc` varied slightly but averaged around **203 milliseconds**, while our custom `malloc` took around **413 milliseconds**. When averaging out those times we got a time of **6 milliseconds** per workload iteration with our 'malloc' versus **3 milliseconds** per iteration of regular 'malloc'.


| Allocation Method | AVG Time (ms) |
|-------------------|---------------|
| mymalloc          | 6             |
| malloc            | 3             |


