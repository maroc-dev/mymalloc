#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"
// malloc() and immediately free() a 1-byte object, 120 times.
int main()
{
    int *a = mymalloc(sizeof(char));

    printf("Testing: %p", a);

    int *arr = mymalloc(sizeof(int) * 10);

    for (int i = 0; i <10; i++){
        arr[i] = i;
    }
    myfree(arr);

    printf("Test 1");
    for (int i = 0; i < 120; i++){
      char *blob = mymalloc(sizeof(char)); //malloc and immediately deallocate an object of 1 byte 120 times
      if (blob == NULL){
        printf("error");
      }
        myfree(blob);
    }
}
