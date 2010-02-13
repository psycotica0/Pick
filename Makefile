.PHONY: clean

CC=gcc
CFLAGS=-Wall -ansi -pedantic -O

pick: pick.o chunk_string.o

%.o: chunk_string.h

clean:
	$(RM) pick
	$(RM) pick.o
	$(RM) chunk_string.o
