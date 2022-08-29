CC=egcc
PROG=sierpinski
CFLAGS=-Wall -g -std=c99
SRC=main.c

PREFIX=[MAKE]

.PHONY: compile clean run

compile: $(SRC) 
	@echo '$(PREFIX) Compiling'
	@$(CC) $(CFLAGS) `sdl2-config --cflags --libs`  -o $(PROG) $(SRC)

clean:
	@echo '$(PREFIX) Cleaning'
	@rm -f $(PROG)
	@rm -f *.core

run:
	@echo '$(PREFIX) Running'
	@./$(PROG)

