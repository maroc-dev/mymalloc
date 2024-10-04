#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"


int main(){
     printf("Test 5 pt 1: freeing an already deallocated pointer \n");
      char *blob = malloc(sizeof(char));
      if (blob == NULL){
        printf("error, not allocating");
      }
        free(blob);
        free(blob); // second free should make error

      printf("Test 5 pt 2: freeing NULL \n");
      char *noChunk = NULL;
      free(noChunk);  // Freeing NULL should work?

      printf("Test 5 pt 3: \n");
      int *p = malloc(100);
	    free(p+1); //should make error
	  
      printf("Test 5 pt 4 \n");
      int *p = malloc(100);
	    int *q = p;
	    free(p);
	    free(q); // should make error
	

}
