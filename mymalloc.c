#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset
#include "mymalloc.h"

// Compile with -DDEBUG to debug
#ifndef DEBUG
#define DEBUG 0
#endif

static union
{
    char bytes[MEMSIZE];
    double not_used; // To ensure alignment
} heap;

typedef struct metadata
{
    unsigned char used;
    unsigned int data_block;
} metadata;

static int isInit = false;

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
    } while (i < MEMSIZE && allocated != 0);

    printf("\nEND HEAP\n\n");
}

static void leak_checker(void)
{
    int i = 0;
    metadata *current;
    int allocated;

    int num_objs_leaked = 0;
    int total_leaked = 0;
    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;
        if (current->used == '1')
        {
            num_objs_leaked++;
            total_leaked += allocated;
        }

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);

    if (num_objs_leaked > 0)
        printf("\nmymalloc: %d bytes leaked in %d objects.\n", total_leaked, num_objs_leaked);
}

static void init()
{
    atexit(leak_checker);
    memset(heap.bytes, 0, sizeof(heap.bytes)); // Initialize all bytes to 0

    // Create initial metadata block
    metadata header;
    header.used = '0';                                   // Unallocated
    header.data_block = sizeof(heap.bytes) - HEADERSIZE; // Remaining size for data

    *(metadata *)(&(heap.bytes)) = header; // Store header in heap
}

void *mymalloc(size_t size, char *file, int line)
{
    // Round size up to a multiple of 8
    size = (size + 7) & ~7;

    if (!isInit)
    {
        // Initialize the heap and first metadata block
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

        if (current->used == '0' && (size <= current->data_block) && (i + size + HEADERSIZE == MEMSIZE))
        {
            current->used = '1';
            current->data_block = size;

            return &(heap.bytes[i + HEADERSIZE]);
        }

        if (current->used == '0' && size + HEADERSIZE <= current->data_block)
        {
            current->used = '1';
            current->data_block = size + HEADERSIZE;
            if (allocated > size + HEADERSIZE)
            {
                metadata new_header;
                new_header.used = '0';
                new_header.data_block = allocated - (size + HEADERSIZE);
                *(metadata *)(&(heap.bytes[i + size + HEADERSIZE])) = new_header;
            }
            if (DEBUG)
                print_heap();
            return &(heap.bytes[i + HEADERSIZE]);
        }

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);

    if (DEBUG)
        print_heap();
    printf("\nmalloc: Unable to allocate %ld bytes (%s:%d)\n", size, file, line);
    return NULL;
}

static void coalesce()
{
    int i = 0;
    metadata *current;
    metadata *next;
    int allocated;
    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;
        if (i + allocated >= MEMSIZE)
            break;

        next = (metadata *)&heap.bytes[i + allocated];

        if (current->used == '0' && next->used == '0')
        {
            current->data_block += next->data_block; // Merge blocks
            continue;                                // Recheck same block for further merging
        }

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);
}

void myfree(void *ptr, char *file, int line)
{
    if (ptr == NULL)
    {
        printf("\nfree: Invalid pointer address (%s:%d)\n", file, line);
        return;
    }

    if (ptr < (void *)heap.bytes || ptr >= (void *)(heap.bytes + MEMSIZE))
    {
        printf("\nfree: Invalid pointer address (%s:%d)\n", file, line);
        exit(2);
    }

    int i = 0;
    metadata *current;
    int allocated;

    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;

        if (current->used == '1' && &(heap.bytes[i + HEADERSIZE]) == ptr)
        {
            current->used = '0'; // Mark as free
            coalesce();          // Attempt to merge adjacent free blocks
            if (DEBUG)
                print_heap();
            return;
        }

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);

    printf("\nfree: Invalid pointer (%s:%d)\n", file, line);
    exit(2);
}