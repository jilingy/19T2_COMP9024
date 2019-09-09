CC	= 9024 dcc
CFLAGS	= -Wall -Werror -std=gnu11 -g

.PHONY: all
all:	puzzle

puzzle:	puzzle.o boardADT.o
puzzle.o: puzzle.c boardADT.h
boardADT.o: boardADT.c boardADT.h

.PHONY: clean
clean:
	-rm -f puzzle puzzle.o
	-rm -f boardADT boardADT.o

