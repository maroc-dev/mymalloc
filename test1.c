#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
//#include "mymalloc.h"

int main()
{
    int *a = malloc(sizeof(char));

    printf("Testing: %p", a);

    int *arr = malloc(sizeof(int) * 10);

    for (int i = 0; i <10; i++){
        arr[i] = i;
    }
    free(arr);

    printf("Test 1");
    for (int i = 0; i < 120; i++){
      char *blob = malloc(sizeof(char)); //malloc and immediately deallocate an object of 1 byte 120 times
      if (blob == NULL){
        printf("error");
      }
        free(blob);
    }
}
