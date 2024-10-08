# mymalloc
A implementation of a malloc and free in c 

## Authors
maf407 - Marco Ferreira 
raj123 - Ryan Jones

Requirements:
1. malloc() reserves unallocated memory.
2. When successful, malloc() returns a pointer to an object that does not overlap with any other
allocated object.
3. free() deallocates memory
4. malloc() and free() arrange so that adjacent free blocks are coalesced
5. Report if there are memory leaks at the programs end
6. Report if malloc could not allocate memory.
7. Report if there was given an invalid pointer
8. Errors report with line numbers and what file the error was in.

Our testing plan is guided by these requirements.

### Memgrind Workloads (Testing plan)

Our `Memgrind` consists of the three given workloads, as well as two of our own creation.

1. **Workload 1**: malloc() and immediately free() a 1-byte object, 120 times.

2. **Workload 2**: Use malloc() to get 120 1-byte objects, storing the pointers in an array, then use free() to deallocate the chunks.

3. **Workload 3**: Create an array of 120 pointers. Repeatedly make a random choice between allocating a 1-byte object and adding the pointer to the array and deallocating a previously allocated object (if any), until you have allocated 120 times. Deallocate any remaining objects.

4. **Workload 4**: Fill the heap with 32-byte chunks, deallocate the last two 32 byte chunk, and try to allocate a 64-byte chunk. This tests that our coalescing mechanism works properly.
   
5. **Workload 5**: Allocate 30 chunks of random sizes between 1 and 64 bytes, then deallocate them in reverse order.

These two workloads are implemented in `test4.c` and `test6.c`. The entire workload in `memgrind` was run 50 times. Memgrind also tested the performance of our mymalloc. We then compared the results to the real malloc

Running: make memgrind

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

To run any of these tests do:
make (testname) # put as many tests in here 
Example: make test2 test3

### Memgrind Runtime

We used `gettimeofday()` to measure the runtime of our `Memgrind`. Regular `malloc` varied slightly but averaged around **203 milliseconds**, while our custom `malloc` took around **413 milliseconds**. When averaging out those times we got a time of **6 milliseconds** per workload iteration with our 'malloc' versus **3 milliseconds** per iteration of regular 'malloc'.


| Allocation Method | AVG Time (ms) |
|-------------------|---------------|
| mymalloc          | 6             |
| malloc            | 3             |

## Library

This section covers functions to use and their purpose.

### `malloc()`

#### Description
Allocates a block of memory of the requested size from a fixed heap. The heap is initialized on the first call. Returns `NULL` if the allocation fails.

#### Prototype
```c
void *malloc(size_t size, char *file, int line);

```

Example usage:
```c
int *arr = (int *)malloc(10 * sizeof(int));
if (arr == NULL) {
    printf("Allocation failed!\n");
}
```

### `free()`
#### Description
Deallocates memory previously allocated by malloc(), merging adjacent free blocks to reduce fragmentation.

#### Prototype

```c
void myfree(void *ptr, char *file, int line);
``` 
Example usage:

```c
free(arr);
```
### Debugging
Compile with -DDEBUG to print heap states.
```bash
gcc -DDEBUG myallocator.c -o myallocator
```

You can find example implementations in `example.c`.
Run: make example to view 