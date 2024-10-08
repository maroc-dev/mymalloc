#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "../mymalloc.h"

int main()
{ // attempting to malloc a chunk with a negative size, this is supposed to crash
    void *negative = malloc(-8);
    free(negative);
}
