#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

int main(){ // attempting to malloc a chunk with a negative size
    void *negative = malloc(-8); 
    free(negative);
}
