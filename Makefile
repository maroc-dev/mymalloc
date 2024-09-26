CC = gcc
CFLAGS = -std=c99 -Wall -Wvla -fsanitize=address,undefined

test: test.o mymalloc.o
	$(CC) $(CFLAGS)  test.o mymalloc.o -o test
	./test.out

test.o:  test.c
	$(CC) $(CFLAGS)  -c test.c 
	

mymalloc.o: mymalloc.c
	$(CC) $(CFLAGS)  -c mymalloc.c 

clean:
	rm -f $(PROGRAM) $(PROGRAM).out
