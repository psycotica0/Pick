#include "chunk_list.h"

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
