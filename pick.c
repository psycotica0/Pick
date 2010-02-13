#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "chunk_string.h"

/* This gives a number in the range of low and high, inclusively. */
/* That is, randBetween(1,5) could give 1,2,3,4,5. */
int randBetween (int low, int high) {
	return (random() % (high - low + 1)) + low;
}

int main (int argc, char* argv[]) {
	/* This holds the current line */
	string_chunk* current = new_chunk_string();
	/* This is my array of output registers */
	string_chunk** values = NULL;
	/* This is the number of random values we've been asked for */
	long requested = 1;
	/* This is the number of lines we've read thus far. */
	int number = 0;
	/* This is just a counter for the for loops. */
	long i;

	if (argc > 1) {
		char* end;
		requested = strtol(argv[1], &end, 10);
		if (end == argv[1]) {
			/* Invalid Number */
			fputs("Only Argument Must Be A Number\n", stderr);
			exit(1);
		} else if (requested <= 0) {
			fputs("Number Must Be A Positive Integer\n", stderr);
			exit(1);
		}
	}

	/* Allocate All My Value Registers */
	values = malloc(sizeof(string_chunk*) * requested);
	/* And Initialize them to empty strings */
	for(i = 0; i < requested; i++) {
		values[i] = new_chunk_string();
	}

	#ifdef S_RAND_DEV
	/* I like srandomdev better, but it's only on BSD */
	srandomdev();
	#else
	srandom(time(NULL));
	#endif

	while (!feof(stdin)) {
		if (chunk_readline(stdin, current) > 0) {
			/* Not a blank line */
			number++;
			for (i = 0; i < requested; i++) {
				/* Now we make a random number between 1 and number. If it's 1, we copy the current line to the current register. Otherwise, we leave it as it is. */
				/* This should, as number increases, guarantee that by the end, all lines will have had equal 1/n chance of making it to the end. */
				if (randBetween(1,number) == 1) {
					/* We should now copy current to the value register */
					chunk_string_copy(current, values[i]);
				}
			}
		}
	}

	for (i = 0; i < requested; i++) {
		chunk_printline(stdout, values[i]);
		putc('\n', stdout);
	}
	return 0;
}
