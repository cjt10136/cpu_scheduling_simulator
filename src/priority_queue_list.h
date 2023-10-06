#pragma once

#include "Process.h"

#include <stdbool.h>

// Using linked list to implement priority queue

typedef struct priority_queue_node {
	Process p;
	struct queue_node* next;
} Priority_queue_node;

typedef struct priority_queue_list {
	Priority_queue_node* front;
} Priority_queue_list;

// constructor and destructor
void priority_queue_list_ctor(Priority_queue_list* q);
void priority_queue_list_dtor(Priority_queue_list* q);

Process* priority_queue_list_top(const Priority_queue_list* q);

bool priority_queue_list_empty(const Priority_queue_list* q);

void priority_queue_list_push(Priority_queue_list* q, const Process* x);
void priority_queue_list_pop(Priority_queue_list* q);
