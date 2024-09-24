#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{
    int *a = malloc(sizeof(char));

    printf("Testing: %p", a);

    return EXIT_SUCCESS;
}