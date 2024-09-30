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

    int *c = malloc(sizeof(int) * 20);

    for (int i = 0; i < 5; i++)
    {
        c[i] = 'c';
    }

    print_heap();

    free(b);
    print_heap();

    int *d = malloc(sizeof(int) * 32);

    for (int i = 0; i < 32; i++)
    {
        d[i] = 'd';
    }

    free(c);
    free(d);

    print_heap();

    return EXIT_SUCCESS;
}