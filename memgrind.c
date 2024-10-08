#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"
#include <sys/time.h>

long getTimeMS() {
    struct timeval time;
    gettimeofday(&time, NULL);
    // Convert seconds to milliseconds and microseconds to milliseconds
    return (time.tv_sec * 1000) + (time.tv_usec / 1000);
}

int main() {
    printf("workload starts NOW\n");
    long startTime, endTime, elapsedTime;

    startTime = getTimeMS(); //get our starting time
    for (int t = 0; t < 50; t++) {
        printf("Test 1\n");
        for (int i = 0; i < 120; i++) {
            char *blob = malloc(sizeof(char)); // malloc and immediately deallocate an object of 1 byte 120 times
            if (blob == NULL) {
                printf("error");
            }
            free(blob);
        }

        printf("Test 2\n");
        char **TestArray = malloc(sizeof(char *) * 120); // initialize an array 120 long
        for (int i = 0; i < 120; i++) {
            TestArray[i] = malloc(sizeof(char)); // allocate memory for each pointer
        }

        for (int i = 0; i < 120; i++) {
            free(TestArray[i]); // free each element
        }
        free(TestArray); // finally free array of pointers
 
        printf("Test 3\n");
        void *PointArray[120]; // create an array for pointers
        int allocatedCount = 0; // track how many allocations have been made

        // Initialize the array to NULL to avoid freeing uninitialized pointers
        for (int i = 0; i < 120; i++) {
            PointArray[i] = NULL;
        }

        // Randomly allocate or deallocate 120 objects
        while (allocatedCount < 120) {  // make sure to allocate exactly 120 times
            int r = rand() % 2; // random between 0 and 1

            if (r == 1 && allocatedCount < 120) {  // allocate if random == 1
                // Find first empty slot
                for (int j = 0; j < 120; j++) {
                    if (PointArray[j] == NULL) {
                        PointArray[j] = malloc(1);  // allocate a 1-byte object and add the pointer to the array
                        allocatedCount++;
                        break;
                    }
                }
            } else if (r == 0 && allocatedCount > 0) {  // deallocate if random == 0 and something is allocated
                // Find first allocated slot
                for (int j = 0; j < 120; j++) {
                    if (PointArray[j] != NULL) {
                        free(PointArray[j]);  // deallocate previously allocated object
                        PointArray[j] = NULL;  // set pointer to NULL after freeing
                        allocatedCount--;
                        break;
                    }
                }
            }
        }

        // Ensure any remaining objects are freed at the end
        for (int i = 0; i < 120; i++) {
            if (PointArray[i] != NULL) {
                free(PointArray[i]);
            }
        }

        printf("Test 4: testing coalescing\n");

        void *chunks[57]; // assume 1000 chunks is enough to fill all available memory space
        int chunk_count = 0; // counter for array 

    // Fill memory with 64-byte chunks
    while (1) { 
        void *chunk = malloc(64); // allocate a 64-byte chunk ONE CHUNK DOESNT GET FREED IN REGULAR MALLOC BUT ALL FREED IN MYMALLOC
        if (chunk == NULL || chunk_count > 56) { 
            printf("Memory is full after allocating %d 64-byte chunks.\n", chunk_count);
            break;
        }
        printf("Allocated chunk %d at %p\n", chunk_count, chunk); // Print the address of each allocated chunk
        chunks[chunk_count++] = chunk;  // Store the pointer in the array
    }

    // Free two adjacent chunks
    if (chunk_count >= 2) { // Check if at least two chunks were allocated
        printf("Freeing chunks %d and %d at %p and %p\n", 
        chunk_count - 1, chunk_count - 2, 
        chunks[chunk_count - 1], chunks[chunk_count - 2]);
    
    free(chunks[chunk_count - 1]);  // free the last chunk
    chunks[chunk_count - 1] = NULL;  // Prevent double-free
    free(chunks[chunk_count - 2]);  // free the second-to-last chunk
    chunks[chunk_count - 2] = NULL;  // Prevent double-free
    printf("Freed two 64-byte chunks.\n");
} else {
    printf("Not enough chunks allocated to free two consecutive chunks.\n");
}

    // Try to allocate a 128-byte chunk to test coalescing
    void *large_chunk = malloc(128);
    if (large_chunk != NULL) {
        printf("Successfully allocated a 128-byte chunk at %p. Coalescing works!\n", large_chunk);
    } else {
        printf("Failed to allocate a 128-byte chunk. Coalescing did not work.\n");
    }

    // Free all remaining chunks
    for (int i = 0; i < chunk_count; i++) {
        if (chunks[i] != NULL) { // if there's STILL SOMETHING THERE AT ALL IN THE ENTIRE CHUNKS POINBTER ARRAY
            free(chunks[i]); // Free the allocated chunk
            printf("Freed memory at pointers[%d]\n", i);
            chunks[i] = NULL; // Prevent double-free 
        }
    }
    //free(chunks[0]);
    

    // Free the large chunk if allocated
    if (large_chunk != NULL) {
        free(large_chunk);
        printf("large chunk freed\n");
        large_chunk = NULL; // Prevent double-free
    }


        
        
        printf("Test 5\n");
        void *pointers[120]; // array to store pointers to allocated memory
        int sizes[120]; // array to store the sizes of the allocated chunks

        // Allocate random-sized chunks
        for (int i = 0; i < 30; i++) { 
            sizes[i] = (rand() % 64) + 1;  // random size between 1 and 64 bytes
            pointers[i] = malloc(sizes[i]);  // allocate memory chunk
            if (pointers[i] == NULL) {
                printf("Memory allocation failed at iteration %d\n", i);
                exit(EXIT_FAILURE);
            }
            //printf("Allocated %d bytes at pointers[%d]\n", sizes[i], i); // print allocation details
        }

        // Free in reverse order
        for (int i = 119; i >= 0; i--) { 
            if (pointers[i] != NULL) {    // Check if pointer is not NULL before freeing
                free(pointers[i]);        // Free the chunk
                //printf("Freed memory at pointers[%d]\n", i);
                pointers[i] = NULL;       // Set pointer to NULL after freeing
            }
        }
    }
    endTime = getTimeMS(); //get our end time
    elapsedTime = endTime - startTime; //get our elapsed time, written in milliseconds
    printf("Elapsed time: %ld milliseconds\n", elapsedTime);


    return 0;
}
