#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

int main()
{
    long* p = malloc(10 * sizeof(long)); // allocate memory for 10 longs
    for(int i = 0; i < 10; i++){
        p[i] = i; // array of allocated memory to i
    }
    for(int i = 9; i >= 0; i--){ // working backwards through the memory array
        printf("address: %p, value: %ld\n",(void*)(p + i), p[i]); //print them out
     }
    free(p); // then free the array

    return 0;
}
