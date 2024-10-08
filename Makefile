CC = gcc
CFLAGS = -std=c99 -Wall -Wvla -fsanitize=address,undefined -g

TARGETS = mymalloc example memtest memgrind
TESTS = test test1 test2 test3 test4 test5 test6 test7 test8 test9 test10
OBJ = $(TESTS:.c=.o)

example: example.o mymalloc.o
	$(CC) $(CFLAGS)  example.o mymalloc.o -o example
	./example

$(TESTS): %: tests/%.c mymalloc.o
	$(CC) $(CFLAGS) -o $@ $< mymalloc.o
	./$@
	

memtest: memtest.o mymalloc.o
	$(CC) $(CFLAGS)  memtest.o mymalloc.o -o memtest
	./memtest 

example.o:  example.c
	$(CC) $(CFLAGS)  -c example.c 

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
	rm -f *.o *.o $(TESTS)

