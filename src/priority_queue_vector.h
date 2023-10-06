#pragma once

#include "Process.h"

#include <stdbool.h>

// Using min-heap to implement priority queue

typedef struct priority_queue_vector {
	int end;		// size of the queue
	int capacity;	// allocate size
	Process* data;
} Priority_queue_vector;

// constructor and destructor
void priority_queue_vector_ctor(Priority_queue_vector* q);
void priority_queue_vector_dtor(Priority_queue_vector* q);

Process* priority_queue_vector_top(const Priority_queue_vector* q);

bool priority_queue_vector_empty(const Priority_queue_vector* q);

void priority_queue_vector_push(Priority_queue_vector* q, const Process* x);
void priority_queue_vector_pop(Priority_queue_vector* q);
