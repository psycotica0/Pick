#include <stdlib.h>
#include <stdio.h>
#include "chunk_string.h"
#include "chunk_list.h"

/* On BSD, srandomdev() is better */
#ifndef seedRand
#define seedRand srandom(time(NULL))
#endif

int main (int argc, char* argv[]) {
	chunk_list* list = NULL;
	string_chunk* current = NULL;
	int number = 0;

	list = malloc(sizeof(chunk_list));
	list->next = NULL;
	list->value = NULL;

	while (!feof(stdin)) {
		current = newString(list);
		if (chunk_readline(stdin, current) > 0) {
			number++;
		}
	}

	seedRand;
	number = random() % number;

	chunk_printline(stdout, getChunk(list, number));
	return 0;
}
