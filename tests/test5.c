#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"


int main(){
     printf("Test 5 pt 1: freeing an already deallocated pointer \n");
      char *blob = mymalloc(sizeof(char));
      if (blob == NULL){
        printf("error, not allocating");
      }
        myfree(blob);
        myfree(blob); // second free should make error

    printf("Test 5 pt 2: freeing NULL \n");
    char *noChunk = NULL;
    myfree(noChunk);  // Freeing NULL 

    printf("Test 5 pt 3: ");
    char *chunk = mymalloc(sizeof(char)); //create chunk
    myfree(chunk); // free the chunk
    char *chunk = mymalloc(sizeof(char)); //recreate the chunk
    myfree(chunk); // free the chunk again
}
