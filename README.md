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


 

   Our Memgrind consists of the three given workloads as well as 2 of our own making. The first of which is to fill the heap with 64 byte chunks until there is no space left, deallocate the last 2 chunks and try to allocate a 128 byte chunk. This would also test that our coalescing works. The second workload would allocate 30 chunks of random sizes between 1 and 64 bytes and then deallocate them in reverse. These two workloads are also stated in test4.c and test6.c. The entire workload in memgrind was ran 50 times.

   In addition, we created more tests to determine that our malloc functioned properly. The workload in memgrind consists of test1,2,3,4, and 6.c but additionally we have:
   test5.c: choosing a number between 1 and 4 lets the function perform a specific test to or state an error: 1- Freeing an already deallocated pointer, 2- Freeing Null which won't work for our malloc and will give us a message stating so, 3- freeing an offset pointer, or 4- double freeing a chunk.
   test7.c: allocating 10 long chunks, printing them out backwards, and then freeing them
   test8.c: allocating memory for a long chunk, the size of a long, then printing out the address and byte size
   test9.c: attempting to allocate memory of a chunk that is a negative size of bytes, should not work.

    Memgrind runtime: We used gettimeofday() to get the runtime of our Memgrind. Regular malloc varied by a couple seconds but mainly gave us around 203 milliseconds. Our malloc ran around 413 milliseconds.






Our Memgrind consists of the three given workloads as well as 2 of our own making. The first of which is to fill the heap with 64 byte chunks until there is no space left, deallocate the last 2 chunks and try to allocate a 128 byte chunk. This would also test that our coalescing works. The second workload would
