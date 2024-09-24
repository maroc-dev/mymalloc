
PROGRAM = first

all: $(PROGRAM)

$(PROGRAM): $(PROGRAM).c
	gcc -Wall -Werror -fsanitize=address,undefined -g -o $(PROGRAM).out $(PROGRAM).c -lm

clean:
	rm -f $(PROGRAM) $(PROGRAM).out

run: $(PROGRAM)
	./$(PROGRAM)

test:
	./$(PROGRAM).out
