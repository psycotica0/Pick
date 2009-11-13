.PHONY: clean

pick: pick.c chunk_string.o chunk_string.h 
	$(CC) -o pick pick.c chunk_string.o 

chunk_string.o: chunk_string.c chunk_string.h
	$(CC) -c -o chunk_string.o chunk_string.c

clean:
	$(RM) pick
	$(RM) chunk_string.o
	$(RM) chunk_list.o
