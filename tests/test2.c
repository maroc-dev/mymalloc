#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"


int main()
{
    
    printf("Test 2\n");
    char **TestArray = mymalloc(sizeof(char *) * 120); //initialize an array 120 long

    for (int i = 0; i < 120; i++){
        TestArray[i] = mymalloc(sizeof(char)); // allocate memory for each pointer
    }


    for (int i = 0; i < 120; i++){
        myfree(TestArray[i]); // free each element
    }
  myfree(TestArray); // finally free array of pointers

    return 0;
}
