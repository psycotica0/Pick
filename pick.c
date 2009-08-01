#include <stdlib.h>
#include <stdio.h>

#define CHUNK_SIZE 10

typedef struct string_chunk {
	char value[CHUNK_SIZE];
	struct string_chunk* next;
} string_chunk;


int chunk_readline_count(FILE* stream, string_chunk* chunk, int read) {
	char temp;
	int i=0;

	for (i=0; i < CHUNK_SIZE; i++) {
		if (feof(stream)) {
			chunk->value[i]='\0';
			return read;
		}
		temp = fgetc(stream);
		if (temp == EOF || temp == '\0' || temp == '\n') {
			chunk->value[i]='\0';
			return read;
		}
		read++;
		chunk->value[i]=temp;
	}

	if (feof(stream)) {
		chunk->next = NULL;
		return read;
	}

	temp = fgetc(stream);
	if (temp == EOF || temp == '\0' || temp == '\n') {
		chunk->next = NULL;
		return read;
	}

	ungetc(temp, stream);
	chunk->next = malloc(sizeof(string_chunk));
	chunk->next->next = NULL;
	if (chunk->next == NULL) {
		return;
	}

	return chunk_readline(stream, chunk->next, read);
}

int chunk_readline(FILE* stream, string_chunk* chunk) {
	return chunk_readline_count(stream, chunk, 0);
}

void chunk_printline(FILE* stream, string_chunk* chunk) {
	int i=0;
	for (i=0; i < CHUNK_SIZE; i++) {
		if (chunk->value[i] == '\0') {
			return;
		}
		fputc(chunk->value[i], stream);
	}

	if (chunk->next != NULL) {
		chunk_printline(stream, chunk->next);
	}
}

typedef struct chunk_list {
	struct string_chunk* value;
	struct chunk_list* next;
} chunk_list;

string_chunk* getChunk(chunk_list* head, int num) {
	int i=0;
	chunk_list* current=head;

	for (i=1; i <= num; i++) {
		if (current->next == NULL) {
			return NULL;
		}
		current = current->next;
	}

	return current->value;
}

chunk_list* getTail(chunk_list* head) {
	chunk_list* current=head;
	while (current->next != NULL) current=current->next;

	return current;
}

string_chunk* newString(chunk_list* head) {
	chunk_list* tail=getTail(head);

	if (tail->value == NULL) {
		tail->value = malloc(sizeof(string_chunk));
		tail->value->next = NULL;
		return tail->value;
	}

	/* Don't keep blank strings */
	if (tail->value->value[0] == '\0') {
		return tail->value;
	}

	tail->next = malloc(sizeof(chunk_list));
	tail->next->value = NULL;
	tail->next->next = NULL;
	return newString(tail->next);
}

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

	srandomdev();
	number = random() % number;

	chunk_printline(stdout, getChunk(list, number));
	return 0;
}
