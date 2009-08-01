
.PHONY: clean

pick: pick.c
	$(CC) -o pick pick.c

clean:
	$(RM) pick
