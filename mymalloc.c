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

void print_heap()
{
    printf("\nPRINTING HEAP\n");
    int i = 0;
    metadata *current;
    int allocated;
    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;
        printf("Used: %c, Data Block: %u\n", current->used, current->data_block);

        i += allocated;

    } while (i <= MEMSIZE && (heap.bytes[i] == '0' || heap.bytes[i] == '1'));

    for (int i = 0; i < MEMSIZE; i++)
    {
        printf("%c", heap.bytes[i]);
    }

    printf("\nEND HEAP\n\n");
}

static void leak_checker(void)
{
}

void init()
{
    atexit(leak_checker);

    // creates a metadata header
    metadata header;
    header.used = '0';                                   // '0' means unallocated
    header.data_block = sizeof(heap.bytes) - HEADERSIZE; // data block is the size of the heap -8 because of the header

    memcpy(heap.bytes, &header, sizeof(metadata)); // copys over the header data
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
        if (current->used == '0' && size + HEADERSIZE < current->data_block)
        {
            current->used = '1';
            current->data_block = size + HEADERSIZE;
            metadata header;
            header.used = '0';
            header.data_block = allocated - size - HEADERSIZE;
            memcpy(&(heap.bytes[(i + size + HEADERSIZE)]), &header, sizeof(metadata));

            return &(heap.bytes[i + HEADERSIZE]);
        }

        i += allocated;
    } while (i <= MEMSIZE && (heap.bytes[i] == '0' || heap.bytes[i] == '1'));

    int *p = NULL;
    return p;
}

void colaless()
{
    int i = 0;
    metadata *current;
    metadata *next;
    int allocated;
    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;
        next = (metadata *)&heap.bytes[i + allocated];

        if (current->used == '0' && next->used == '0')
        {
            current->data_block += next->data_block;
            continue;
        }

        i += allocated;
    } while (i <= MEMSIZE && (heap.bytes[i] == '0' || heap.bytes[i] == '1'));
}

void myfree(void *ptr, char *file, int line)
{
    // colalessing free allocated space
    int i = 0;
    metadata *current;
    int allocated;

    // freeing
    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;
        if (current->used == '1' && &(heap.bytes[i + HEADERSIZE]) == ptr)
        {
            current->used = '0';
            colaless();
            return;
        }

        i += allocated;
    } while (i <= MEMSIZE && (heap.bytes[i] == '0' || heap.bytes[i] == '1'));

    printf("Pointer not found");
}