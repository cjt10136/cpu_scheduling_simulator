#pragma once

#include "Process.h"

#include <stdbool.h>

// Using circular array to implement queue

typedef struct queue_vector {
	int begin;
	int end;
	int count;		// size of the queue
	int capacity;	// allocate size
	Process* data;
} Queue_vector;

// constructor and destructor
void queue_vector_ctor(Queue_vector* q);
void queue_vector_dtor(Queue_vector* q);

Process* queue_vector_top(const Queue_vector* q);

bool queue_vector_empty(const Queue_vector* q);

void queue_vector_push(Queue_vector* q, const Process* x);
void queue_vector_pop(Queue_vector* q);
