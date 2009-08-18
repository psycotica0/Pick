.PHONY: clean

pick: pick.c chunk_string.o chunk_string.h chunk_list.o chunk_list.h
	$(CC) -o pick pick.c chunk_string.o chunk_list.o

chunk_string.o: chunk_string.c chunk_string.h
	$(CC) -c -o chunk_string.o chunk_string.c

chunk_list.o: chunk_list.c chunk_list.h chunk_string.h
	$(CC) -c -o chunk_list.o chunk_list.c 

clean:
	$(RM) pick
	$(RM) chunk_string.o
	$(RM) chunk_list.o
