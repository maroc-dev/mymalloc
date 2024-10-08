#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include "mymalloc.h"

#define OBJECTS 64
#define OBJSIZE (MEMSIZE / OBJECTS - HEADERSIZE)
#define TOTAL_ALLOCS 120
#define MAX_CHUNKS 100
#define ALLOC_SIZE 32
#define LARGE_ALLOC_SIZE 64 // 2 times larger than the ALLOC_SIZE
#define ITERATIONS 50

// Function to get the current time in milliseconds
long get_time_ms()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

// Test 1: Allocate and immediately deallocate 1-byte objects 120 times
void test_1()
{
    for (int i = 0; i < TOTAL_ALLOCS; i++)
    {
        char *blob = malloc(sizeof(char));
        if (blob == NULL)
        {
            printf("Memory allocation error in Test 1\n");
            exit(EXIT_FAILURE);
        }
        free(blob);
    }
}

// Test 2: Allocate and free memory for an array of 120 elements
void test_2()
{
    char **test_array = malloc(sizeof(char *) * TOTAL_ALLOCS);
    for (int i = 0; i < TOTAL_ALLOCS; i++)
    {
        test_array[i] = malloc(sizeof(char));
    }
    for (int i = 0; i < TOTAL_ALLOCS; i++)
    {
        free(test_array[i]);
    }
    free(test_array);
}

// Test 3: Randomly allocate or deallocate 1-byte objects until exactly 120 allocations have been made
void test_3()
{
    char *point_array[TOTAL_ALLOCS] = {NULL};
    int allocated_count = 0;

    while (allocated_count < TOTAL_ALLOCS)
    {
        int r = rand() % 2; // random between 0 and 1
        if (r == 1 && allocated_count < TOTAL_ALLOCS)
        {
            for (int j = 0; j < TOTAL_ALLOCS; j++)
            {
                if (point_array[j] == NULL)
                {
                    point_array[j] = malloc(sizeof(char));
                    allocated_count++;
                    break;
                }
            }
        }
        else if (r == 0 && allocated_count > 0)
        {
            for (int j = 0; j < TOTAL_ALLOCS; j++)
            {
                if (point_array[j] != NULL)
                {
                    free(point_array[j]);
                    point_array[j] = NULL;
                    allocated_count--;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < TOTAL_ALLOCS; i++)
    {
        if (point_array[i] != NULL)
        {
            free(point_array[i]);
        }
    }
}

// Test 4: Test coalescing by freeing adjacent chunks and attempting to allocate a larger chunk
void test_4()
{
    void *chunks[MAX_CHUNKS] = {NULL}; // Ensure chunks are initialized to NULL
    int chunk_count = 0;

    // Fill memory with 32-byte chunks
    while (chunk_count < MAX_CHUNKS) // Prevent over-allocation
    {
        void *chunk = malloc(ALLOC_SIZE);
        if (chunk == NULL)
        {
            break;
        }
        chunks[chunk_count++] = chunk;
    }

    // Free two adjacent chunks
    if (chunk_count >= 2)
    {
        free(chunks[chunk_count - 1]);
        chunks[chunk_count - 1] = NULL;
        free(chunks[chunk_count - 2]);
        chunks[chunk_count - 2] = NULL;
    }

    // Try to allocate a large chunk to test coalescing
    void *large_chunk = malloc(LARGE_ALLOC_SIZE);
    if (large_chunk != NULL)
    {
        free(large_chunk);
        large_chunk = NULL; // Prevent double-free
    }
    else
    {
        printf("Failed to allocate a %d-byte chunk. Coalescing did not work.\n", LARGE_ALLOC_SIZE);
    }

    // Free all remaining chunks
    for (int i = 0; i < chunk_count; i++)
    {
        if (chunks[i] != NULL)
        {
            free(chunks[i]);  // Free remaining chunks in the array
            chunks[i] = NULL; // Set to NULL to avoid dangling pointers
        }
    }
}

// Test 5: Allocate and deallocate random-sized chunks in reverse
void test_5()
{
    void *pointers[TOTAL_ALLOCS] = {NULL};
    int sizes[TOTAL_ALLOCS] = {0};

    for (int i = 0; i < TOTAL_ALLOCS / 2; i++)
    {
        sizes[i] = (rand() % ALLOC_SIZE) + 1;
        pointers[i] = malloc(sizes[i]);
        if (pointers[i] == NULL)
        {
            printf("Memory allocation failed at iteration %d\n", i);
            exit(EXIT_FAILURE);
        }
    }

    for (int i = TOTAL_ALLOCS - 1; i >= 0; i--)
    {
        if (pointers[i] != NULL)
        {
            free(pointers[i]);
            pointers[i] = NULL;
        }
    }
}

int main()
{
    printf("Workload starts NOW\n");

    long start_time = get_time_ms(); // Get starting time
    for (int i = 0; i < ITERATIONS; i++)
    {
        test_1();
        test_2();
        test_3();
        test_4();
        test_5();
    }

    long end_time = get_time_ms(); // Get ending time
    long elapsed_time = end_time - start_time;

    printf("Elapsed time: %ld milliseconds\n", elapsed_time);

    return EXIT_SUCCESS;
}
