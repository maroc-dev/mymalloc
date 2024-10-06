#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

int main(){
    // workload will be made up of test1, 2, 3, 4, and 6
    printf("workload starts NOW");


    for (int t = 0; t < 50; t++){
        printf("Test 1\n");
        for (int i = 0; i < 120; i++){
            char *blob = malloc(sizeof(char)); //malloc and immediately deallocate an object of 1 byte 120 times
            if (blob == NULL){
                printf("error");
             }
        free(blob);
        }

         printf("Test 2\n");
        char **TestArray = malloc(sizeof(char *) * 120); //initialize an array 120 long

        for (int i = 0; i < 120; i++){
            TestArray[i] = malloc(sizeof(char)); // allocate memory for each pointer
        }


        for (int i = 0; i < 120; i++){
            free(TestArray[i]); // free each element
        }
        free(TestArray); // finally free array of pointers
        

        printf("Test 3\n");
        void *PointArray[120]; // create an array for pointers
    
        for (int i = 0; i < 120; i++){
            PointArray[i] = NULL; //initialize the array to null to avoid freeing uninitialized pointers
        }
        for (int i = 0; i < 120; i++){
            int r = rand() % 2; //random between 0 and 1
            if (r==1){ // Repeatedly make a random choice between allocating a 1-byte object and deallocating previously allocated block
            char *AThing = malloc(1);  // allocate a 1 byte object and add the pointer to the array
            PointArray[i] = AThing;
            } else if (r == 0 && i > 0 && PointArray[i - 1] != NULL) { // if result is zero and previous slot is not empty
                // Deallocate a previously allocated object
                free(PointArray[i - 1]);
                PointArray[i - 1] = NULL;  // Set the pointer to NULL after freeing
            }
        }
    
    
    
    }





}
