#ifndef _CHUNK_LIST_H
#define _CHUNK_LIST_H

#include <stdlib.h>
#include "chunk_string.h"

typedef struct chunk_list {
	struct string_chunk* value;
	struct chunk_list* next;
} chunk_list;

string_chunk* getChunk(chunk_list*, int);

chunk_list* getTail(chunk_list*);

string_chunk* newString(chunk_list*);


#endif

