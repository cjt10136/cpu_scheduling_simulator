#pragma once

#include "Process.h"

#include <stdbool.h>

// Using linked list to implement queue

typedef struct queue_node {
	Process p;
	struct queue_node* next;
} Queue_node;

typedef struct queue_list {
	Queue_node* front;	// pop from front
	Queue_node* back;	// insert to back
} Queue_list;

// constructor and destructor
void queue_list_ctor(Queue_list* q);
void queue_list_dtor(Queue_list* q);

Process* queue_list_top(const Queue_list* q);
bool queue_list_empty(const Queue_list* q);

void queue_list_push(Queue_list* q, const Process* x);
void queue_list_pop(Queue_list* q);
