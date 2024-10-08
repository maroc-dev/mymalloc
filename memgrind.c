#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

#define OBJECTS 120

void deallocate(void **PointArray)
{
    for (int i = 0; i < OBJECTS; i++)
    {
        if (PointArray[i] != NULL)
        {
            printf("\n%d\n", i);
            free(PointArray[i]);

            PointArray[i] = NULL;
            return;
        }
    }
}

void deallocate_all(void **PointArray)
{
    for (int i = 0; i < OBJECTS; i++)
    {
        if (PointArray[i] != NULL)
        {
            free(PointArray[i]);
            PointArray[i] = NULL;
        }
    }
}

int main()
{
    // workload will be made up of test1, 2, 3, 4, and 6
    printf("workload starts NOW");

    for (int t = 0; t < 1; t++)
    {
        printf("\nTest 1\n");
        for (int i = 0; i < OBJECTS; i++)
        {
            char *blob = malloc(sizeof(char)); // malloc and immediately deallocate an object of 1 byte OBJECTS times
            if (blob == NULL)
            {
                printf("error");
            }
            free(blob);
        }

        print_heap();

        printf("Test 2\n");
        char **TestArray = malloc(sizeof(char *) * OBJECTS); // initialize an array OBJECTS long

        for (int i = 0; i < OBJECTS; i++)
        {
            TestArray[i] = malloc(sizeof(char)); // allocate memory for each pointer
        }

        for (int i = 0; i < OBJECTS; i++)
        {
            free(TestArray[i]); // free each element
        }
        free(TestArray); // finally free array of pointers
        print_heap();

        printf("Test 3\n");

        void *PointArray[OBJECTS]; // create an array for pointers

        for (int i = 0; i < OBJECTS; i++)
        {
            PointArray[i] = NULL; // initialize the array to null to avoid freeing uninitialized pointers
        }

        int total_allocated = 0;

        for (int i = 0; total_allocated <= OBJECTS; i++)
        {
            printf("This");
            int r = rand() % 2; // random between 0 and 1
            if (r == 1)
            {                                         // Repeatedly make a random choice between allocating a 1-byte object and deallocating previously allocated block
                PointArray[i] = malloc(sizeof(char)); // allocate a 1 byte object and add the pointer to the array

                if (PointArray[i] == NULL)
                {
                    printf("Malloc failed!\n");
                    break;
                }
                print_heap();
                total_allocated++;
                printf("\nAllocated: %p\t at index: %d\n", PointArray[i], i);
            }
            else if (r == 0)
            { // if result is zero and previous slot is not empty
                // Deallocate a previously allocated object
                printf("\nFreeing\n");
                // deallocate(PointArray);
            }
        }
        deallocate_all(PointArray);
    }
}
