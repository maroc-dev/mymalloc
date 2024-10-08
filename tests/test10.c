#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../mymalloc.h"

int main()
{ // allocate a chunk using arithmetic to determine size, try to print the address of the chunk after freeing it
    void *p = malloc(4 + 8);
    printf("Allocated memory at address: %p\n", p);
    free(p);
}
