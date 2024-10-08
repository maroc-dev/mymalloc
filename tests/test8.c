#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"


int main(){
    long *problemChild = malloc(sizeof(long)); //allocate memory for a long chunk, size of a long
    printf("Address: %p\n", (void*)problemChild); // print the address of the chunk
    printf("bytes: %zu\n", sizeof(long)); //print the byte size of the chunk
}
