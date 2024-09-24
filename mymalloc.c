#include <stdio.h>
#include <stdlib.h>

#include "mymalloc.h"

static union
{
    char bytes[MEMSIZE];
    double notUsed;
} heap;

int isInit = false;

void init(size_t size)
{
    for (int i = 0; i < HEADERSIZE; i++)
    {
        heap.bytes[i] = 0;
    }
}

void *mymalloc(size_t size, char *file, int line)
{
    // round size to nearest byte here

    if (!isInit)
    {
        // initializes the heap, adds the first metadata block
        init(size);
        isInit = true;
    }

    int allocating = false;

    char current = heap.bytes[0];

    do
    {
        if (current == 0)
        {
                }
    } while (allocating);

    int *p = NULL;
    return p;
}