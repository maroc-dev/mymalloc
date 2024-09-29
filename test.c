#include <stdio.h>
#include <stdlib.h>
#include "mymalloc.h"

int main()
{
    int size = 1;
    int *a = malloc(sizeof(int) * size);

    printf("Testing: %p", a);

    for (int i = 0; i < size; i++)
    {
        a[i] = i;
    }

    for (int i = 0; i < size; i++)
    {
        printf("\n%d\n", a[i]);
    }

    int sizeb = 90;
    int *b = malloc(sizeof(int) * sizeb);

    for (int i = 0; i < sizeb; i++)
    {
        b[i] = i;
    }

    for (int i = 0; i < sizeb; i++)
    {
        printf("\n%d\n", b[i]);
    }

    int sizec = 10;
    int *c = malloc(sizeof(int) * sizec);

    for (int i = 0; i < sizec; i++)
    {
        c[i] = i;
    }

    for (int i = 0; i < sizec; i++)
    {
        printf("\n%d\n", c[i]);
    }

    a[0] = 1000;
    b[0] = 2000;
    c[0] = 3000;

    printf("Testing: %d, %d, %d", a[0], b[0], c[0]);

    return EXIT_SUCCESS;
}