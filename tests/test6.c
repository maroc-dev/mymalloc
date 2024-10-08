#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../mymalloc.h"

int main()
{
    void *pointers[120]; // array to store pointers to allocated memory
    int sizes[120];      // array to store the sizes of the allocated blocks

    for (int i = 0; i < 120; i++)
    {                                   // do the following 120 times:
        sizes[i] = (rand() % 64) + 1;   // random size between 1 and 64 bytes
        pointers[i] = malloc(sizes[i]); // allocate memory chunk of size i
        if (pointers[i] == NULL)
        { // in case allocation does not function
            printf("Memory allocation failed at iteration %d\n", i);
            exit(EXIT_FAILURE);
        }
        printf("Allocated %d bytes at pointers[%d]\n", sizes[i], i); // print statement tells us the size we just malloced
    }

    for (int i = 120; i > 0; i--)
    {                      // in reverse order through the array
        free(pointers[i]); // free the chunk of memory at that point in the array
        printf("Freed memory at pointers[%d]\n", i);
    }
}
