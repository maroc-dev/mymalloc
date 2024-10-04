CC = gcc
CFLAGS = -std=c99 -Wall -Wvla -fsanitize=address,undefined

TARGETS = mymalloc test memtest

test: test.o mymalloc.o
	$(CC) $(CFLAGS)  test.o mymalloc.o -o test
	./test

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS)  memtest.o mymalloc.o -o memtest
	./memtest -DLEAK

test.o:  test.c
	$(CC) $(CFLAGS)  -c test.c 
	

mymalloc.o: mymalloc.c
	$(CC) $(CFLAGS)  -c mymalloc.c 

memtest.o: memtest.c
	$(CC) $(CFLAGS)  -c memtest.c

clean:
	rm -f *.o $(TARGETS)
	rm -f *.out $(TARGETS)

