#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "mymalloc.h"

int main()
{

  printf("Test 1\n");
  for (int i = 0; i < 120; i++)
  {
    char *blob = malloc(sizeof(char)); // malloc and immediately deallocate an object of 1 byte 120 times
    if (blob == NULL)
    {
      printf("error");
    }
    free(blob);
  }
}
