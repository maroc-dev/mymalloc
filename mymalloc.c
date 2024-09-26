#include <stdio.h>
#include <stdlib.h>

#include "mymalloc.h"

//this is a comment

static union
{
    char bytes[MEMSIZE];
    double notUsed;
} heap;

int isInit = false;

void init()
{
    for (int i = 0; i < HEADERSIZE; i++)
    {
        heap.bytes[i] = 0;
    }
}

void *mymalloc(size_t size, char *file, int line)
{
    // rounds size up to a multiple of 8
    size = (size + 7) & ~7;

    if (!isInit)
    {
        // initializes the heap, adds the first metadata block
        init(size);
        isInit = true;
    }

    int allocating = false;

    char *current = &heap.bytes[0];
    current[1] = size;

    printf("\n%d\t%d\t%d\t%d\n", current[1], current[2], current[3], current[4]);
    do
    {
        if (current == 0)
        {
        }

        // update current to size of data + 8
    } while (allocating);

    int *p = NULL;
    return p;
}