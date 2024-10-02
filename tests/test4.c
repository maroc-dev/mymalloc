#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    printf("Test 4: testing coallescing\n");

    void *chunks[1000]; // assume 1000 chunks is enough to fill all available memory space
    int chunk_count = 0; // counter for array 

    while(1){ // we're allowed to do continuous loop until break right? otherwise could have flag that indicates when memory full
        void *chunk = mymalloc(64); // allocate a 64 byte chunk
        if (chunk == NULL){ // unless there's another indicator of when memory full, attempting to allocate space in a full memory will give us a chunk of nothing
            printf("Memory is full after allocating %d 64-byte chunks.\n", chunk_count);
            break;
         }
        chunks[chunk_count++] = chunk;  // Store the pointer in the array
    }

    // now that we have a full memory, we need to make some space
    if (chunk_count >= 3) { // we should have enough memory space to allocate at least 3 64 byte chunks, otherwise we have bigger issues
        myfree(chunks[chunk_count - 2]);  //free the second-to-last chunk
        myfree(chunks[chunk_count - 3]);  //free the third-to-last chunk
        printf("Freed two 64-byte chunks.\n");
    } else {
        printf("Not enough chunks allocated to free two consecutive chunks.\n"); // this should not happen at all
        return 1;
    }



    // now that we made space, allocate a 128 size chunk
    void *large_chunk = mymalloc(128);
    if (large_chunk != NULL) {
        printf("Successfully allocated a 128-byte chunk. Coalescing works!\n");
    } else {
        printf("Failed to allocate a 128-byte chunk. Coalescing did not work.\n");
    }
}
