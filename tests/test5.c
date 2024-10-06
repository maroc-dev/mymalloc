#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"


int main(){
     
     int choice;

      printf("Select a test to run (1-4):\n");
      printf("1. Freeing an already deallocated pointer\n");
      printf("2. Freeing NULL\n");
      printf("3. Freeing pointer offset\n");
      printf("4. Double free\n");
      printf("Enter your choice: ");
    
      // Get user input
      scanf("%d", &choice);
     
    if(choice==1){ 
     printf("Test 5 pt 1: freeing an already deallocated pointer \n");
      char *blob = malloc(sizeof(char));
      if (blob == NULL){
        printf("error, not allocating");
      }
        free(blob);
        free(blob); // second free should make error and crash
        printf("if you see this, BAD");
    }

      if(choice==2){
      printf("Test 5 pt 2: freeing NULL \n");
      char *noChunk = NULL;
      free(noChunk);  // Freeing NULL should work?
      printf("i think this works");
      }


      if(choice==3){
      printf("Test 5 pt 3: \n");
      int *point = malloc(100);
	    free(point+1); //should make error and crash
      printf("if you see this, BAD");
      }

      if(choice==4){
      printf("Test 5 pt 4 \n");
      int *p = malloc(100);
	    int *q = p;
	    free(p);
	    free(q); // should make error and crash
      printf("if you see this, BAD");
      }

}
