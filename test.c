#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{
    int *a = malloc(sizeof(int) * 3);

    printf("Testing: %p", a);

    for (int i = 0; i < 3; i++)
    {
        a[i] = i;
    }

    for (int i = 0; i < 3; i++)
    {
        printf("\n%d\n", a[i]);
    }

    return EXIT_SUCCESS;
}