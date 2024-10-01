#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

int main()
{
    int *a = mymalloc(sizeof(char));

    printf("Testing: %p", a);

    int *arr = mymalloc(sizeof(int) * 10);

    for (int i = 0; i <10; i++){
        arr[i] = i;
    }
    myfree(arr);

    

    printf("Test 2\n");
    int **TestArray = mymalloc(sizeof(int) * 120); //initialize an array 120 long, this one is for pointers for ints
    for (int i = 0; i < 120; i++){
        int *AnObject = mymalloc(sizeof(char)); 
        TestArray[i] = AnObject; // store pointers in an array
        myfree(AnObject); // then use free() to deallocate the chunks
    }
}
