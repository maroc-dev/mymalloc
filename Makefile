CC = gcc
CFLAGS = -std=c99 -Wall -Wvla -fsanitize=address,undefined

TARGETS = mymalloc test memtest

test: test.o mymalloc.o
	$(CC) $(CFLAGS)  test.o mymalloc.o -o test
	./test

test.o:  test.c
	$(CC) $(CFLAGS)  -c test.c 
	

mymalloc.o: mymalloc.c
	$(CC) $(CFLAGS)  -c mymalloc.c 

clean:
	rm -f *.o $(TARGETS)
	rm -f *.out $(TARGETS)

