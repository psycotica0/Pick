.PHONY: clean

CC=gcc
CFLAGS=-Wall -ansi -pedantic -O

pick: pick.o chunk_string.o chunk_list.o

%.o: chunk_string.h chunk_list.h

clean:
	$(RM) pick
	$(RM) pick.o
	$(RM) chunk_string.o
	$(RM) chunk_list.o
