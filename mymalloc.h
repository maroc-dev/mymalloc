#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef _MYMALLOC_H
#define _MYMALLOC_H

#define malloc(x) mymalloc(x, __FILE__, __LINE__)
#define free(x) myfree(x, __FILE__, __LINE__)

void *mymalloc(size_t size, char *file, int line);
void myfree(void *ptr, char *file, int line);
void print_heap();

#endif

#define MEMSIZE 4096
#define HEADERSIZE 8
#define true 1
#define false 0
