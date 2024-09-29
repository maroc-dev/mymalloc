#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "mymalloc.h"

static union
{
    char bytes[MEMSIZE];
    double not_used;
} heap;

typedef struct metadata
{
    unsigned char used;
    unsigned int data_block;
} metadata;

int isInit = false;

static void leak_checker(void)
{
}

void init()
{
    atexit(leak_checker);

    for (int i = 0; i < MEMSIZE; i++)
    {
        heap.bytes[i] = '.';
    }

    // creates a metadata header
    metadata header;
    header.used = '0';                          // '0' means unallocated
    header.data_block = sizeof(heap.bytes) - 8; // data block is the size of the heap -8 because of the header

    memcpy(heap.bytes, &header, sizeof(metadata)); // copys over the header data

    printf("size: %ld\n", sizeof(metadata));
}

void *mymalloc(size_t size, char *file, int line)
{
    // rounds size up to a multiple of 8
    size = (size + 7) & ~7;

    if (!isInit)
    {
        // initializes the heap, adds the first metadata block
        init();
        isInit = true;
    }

    int i = 0;
    metadata *current;
    int allocated;

    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;
        printf("Used: %c, Data Block: %u\n", current->used, current->data_block);
        if (current->used == '0' && size < current->data_block)
        {
            current->used = '1';
            current->data_block = size + 8;
            // printf("Used: %c, Data Block: %u\n", current->used, current->data_block);
            metadata header;
            header.used = '0';
            header.data_block = allocated - size - 8;

            memcpy(&heap.bytes[(i + size + 8)], &header, sizeof(metadata));

            // printf("\nSize of header: %u\n", header.data_block);

            // printf("Used: %d, %d\n", current->data_block, header.data_block);

            return &heap.bytes[i + 8];
        }

        i += allocated;

    } while (i <= MEMSIZE);

    int *p = NULL;
    return p;
}