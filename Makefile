CC = gcc
CFLAGS = -std=c99 -Wall -Wvla -fsanitize=address,undefined -g

TARGETS = mymalloc test memtest memgrind

test: test.o mymalloc.o
	$(CC) $(CFLAGS)  test.o mymalloc.o -o test
	./test

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS)  memtest.o mymalloc.o -o memtest
	./memtest 

test.o:  test.c
	$(CC) $(CFLAGS)  -c test.c 

memgrind: memgrind.o mymalloc.o
	$(CC) $(CFLAGS) memgrind.o mymalloc.o -o memgrind
	./memgrind 

memgrind.o: memgrind.c
	$(CC) $(CFLAGS) -c memgrind.c 

mymalloc.o: mymalloc.c
	$(CC) $(CFLAGS)  -c mymalloc.c 

memtest.o: memtest.c
	$(CC) $(CFLAGS)  -c memtest.c

clean:
	rm -f *.o $(TARGETS)
	rm -f *.out $(TARGETS)

