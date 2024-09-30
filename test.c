#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{
    int size = 11;

    int *a = malloc(sizeof(int) * size);

    printf("Testing: %p", a);

    for (int i = 0; i < size; i++)
    {
        a[i] = 'a';
    }

    int *b = malloc(sizeof(double) * (size));

    for (int i = 0; i < (size); i++)
    {
        b[i] = 'b';
    }
    print_heap();

    free(a);
    free(a);

    a = malloc(sizeof(int) * 2);

    for (int i = 0; i < 2; i++)
    {
        a[i] = 'c';
    }

    print_heap();

    printf("Testing: %d\n", b[0]);

    return EXIT_SUCCESS;
}