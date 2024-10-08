#include <stdio.h>
#include <stdlib.h>
#include <string.h> // for memset
#include "mymalloc.h"

// Compile with -DDEBUG to debug
#ifndef DEBUG
#define DEBUG 0
#endif

// Define macros to represent allocation status as characters
#define ALLOCATED '1'
#define FREE '0'

static union
{
    char bytes[MEMSIZE];
    double not_used; // To ensure alignment
} heap;

typedef struct metadata
{
    char used; // Still a char to store single-byte value
    unsigned int data_block;
} metadata;

static int isInit = false;

/**
 * @brief Prints the current state of the heap.
 *
 * This function iterates through the heap and prints whether each block is
 * allocated or free, as well as the size of each block.
 */
static void print_heap()
{
    printf("\nPRINTING HEAP\n");
    int i = 0;
    metadata *current;
    int allocated;
    do
    {
        current = (metadata *)&heap.bytes[i];
        allocated = current->data_block;

        printf("Used: %s, Data Block: %u\n", current->used == ALLOCATED ? "ALLOCATED" : "FREE", current->data_block);

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);

    printf("\nEND HEAP\n\n");
}

/**
 * @brief Checks for memory leaks and prints a summary.
 *
 * This function is called automatically upon program exit using `atexit()`.
 * It scans through the heap and reports the number of leaked objects and the total
 * number of bytes leaked.
 */
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
        if (current->used == ALLOCATED)
        {
            num_objs_leaked++;
            total_leaked += allocated;
        }

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);

    if (num_objs_leaked > 0)
        printf("\nmymalloc: %d bytes leaked in %d objects.\n", total_leaked, num_objs_leaked);
}

/**
 * @brief Initializes the heap and sets up the first free block.
 *
 * This function is called when `mymalloc()` is called for the first time.
 * It initializes the heap with a free block that covers the entire heap size,
 * minus the metadata header size. It also registers the leak checker function
 * to run on program exit.
 */
static void init()
{
    atexit(leak_checker);
    memset(heap.bytes, 0, sizeof(heap.bytes)); // Initialize all bytes to 0

    // Create initial metadata block
    metadata header;
    header.used = FREE;                                  // Unallocated
    header.data_block = sizeof(heap.bytes) - HEADERSIZE; // Remaining size for data

    *(metadata *)(&(heap.bytes)) = header; // Store header in heap
}

/**
 * @brief Allocates memory from the heap.
 *
 * This function allocates `size` bytes from the heap. It searches for a free block
 * large enough to satisfy the request and splits the block if necessary. If no
 * suitable block is found, it returns `NULL`.
 *
 * @param size The number of bytes to allocate.
 * @param file The source file where the allocation request was made (for debugging).
 * @param line The line number in the source file where the allocation request was made (for debugging).
 * @return A pointer to the allocated memory or `NULL` if allocation fails.
 */
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

        if (current->used == FREE && (size <= current->data_block) && (i + size + HEADERSIZE == MEMSIZE))
        {
            current->used = ALLOCATED;
            current->data_block = size;

            return &(heap.bytes[i + HEADERSIZE]);
        }

        if (current->used == FREE && size + HEADERSIZE <= current->data_block)
        {
            current->used = ALLOCATED;
            current->data_block = size + HEADERSIZE;
            if (allocated > size + HEADERSIZE)
            {
                metadata new_header;
                new_header.used = FREE;
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

/**
 * @brief Attempts to coalesce adjacent free blocks into a single block.
 *
 * This function scans the heap and merges adjacent free blocks into a single
 * larger block to reduce fragmentation and maximize the available space.
 */
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

        if (current->used == FREE && next->used == FREE)
        {
            current->data_block += next->data_block; // Merge blocks
            continue;                                // Recheck same block for further merging
        }

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);
}

/**
 * @brief Frees a previously allocated block of memory.
 *
 * This function marks a block of memory as free. It checks if the pointer is valid,
 * then marks the corresponding block as free and attempts to coalesce adjacent free
 * blocks. If the pointer is invalid or was not allocated by `mymalloc()`, the
 * program will print an error message and exit.
 *
 * @param ptr A pointer to the memory block to free.
 * @param file The source file where the free request was made (for debugging).
 * @param line The line number in the source file where the free request was made (for debugging).
 */
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

        if (current->used == ALLOCATED && &(heap.bytes[i + HEADERSIZE]) == ptr)
        {
            current->used = FREE; // Mark as free
            coalesce();           // Attempt to merge adjacent free blocks
            if (DEBUG)
                print_heap();
            return;
        }

        i += allocated;
    } while (i < MEMSIZE && allocated != 0);

    printf("\nfree: Invalid pointer (%s:%d)\n", file, line);
    exit(2);
}
