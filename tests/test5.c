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
    myfree(noChunk);  // Freeing NULL (should work?)

    printf("Test 5 pt 3: ");
    char *chunk = mymalloc(100000000000000); //create chunk too big
    if (p == NULL){
         printf("aa")
              }
     
     printf("Test 5 pt 4: ");
     int *p = malloc(100);
     free(p+1); // should make error
     
}
