#include <stdlib.h>
#include <stdio.h>
#include "chunk_string.h"

string_chunk* newString() {
	string_chunk* ret = NULL;
	ret = malloc(sizeof(string_chunk));
	ret->next = NULL;

	return ret;
}

/* This gives a number in the range of low and high, inclusively. */
/* That is, randBetween(1,5) could give 1,2,3,4,5. */
int randBetween (int low, int high) {
	return (random() % (high - low + 1)) + low;
}

int main (int argc, char* argv[]) {
	string_chunk* current = newString();
	string_chunk* temp = newString();
	int number = 0;

	#ifdef S_RAND_DEV
	/* I like srandomdev better, but it's only on BSD */
	srandomdev();
	#else
	{
		FILE* urand = fopen("/dev/urandom", "r");
		if (urand == NULL) {
			/* If we can't get urand, just use the curent time */
			srandom(time(NULL));
		} else {
			srandom(fgetc(urand));
			fclose(urand);
		}
	}
	#endif

	while (!feof(stdin)) {
		if (chunk_readline(stdin, temp) > 0) {
			/* Not a blank line */
			number++;
			/* Now we make a random number between 1 and number. If it's 1, we swap temp and current. Otherwise, we leave it as it is. */
			/* This should, as number increases, guarantee that by the end, all lines will have had equal 1/n chance of making it to the end. */
			if (randBetween(1,number) == 1) {
				/* We should now swap temp and current */
				{
					string_chunk* swap = current;
					current = temp;
					temp = swap;
				}
			}
		}
	}

	chunk_printline(stdout, current);
	return 0;
}
