#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

int main()
{
    
    printf("Test 3");

    
    void *PointArray[120]; // create an array for pointers

    
    for (int i = 0; i < 120; i++){
        PointArray[i] = NULL; //initialize the array to null to avoid freeing uninitialized pointers
    }
    for (int i = 0; i < 120; i++){
        int r = rand() % 2; //random between 0 and 1
        if (r==1){ // Repeatedly make a random choice between allocating a 1-byte object and deallocating previously allocated block
          char *AThing = malloc(1);  // allocate a 1 byte object and add the pointer to the array
          PointArray[i] = AThing;
        } else if (i == 0 && PointArray[i - 1] != NULL) { // if result is zero and previous slot is not empty
            // Deallocate a previously allocated object
            free(PointArray[i - 1]);
            PointArray[i - 1] = NULL;  // Set the pointer to NULL after freeing
        }
    }
    

    
    return EXIT_SUCCESS;
}
