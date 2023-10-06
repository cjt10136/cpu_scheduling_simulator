#include "Priority_queue_list.h"

#include <assert.h>
#include <stdlib.h>

void priority_queue_list_ctor(Priority_queue_list* q)
{
	q->front = NULL;
}

void priority_queue_list_dtor(Priority_queue_list* q)
{
	for (Priority_queue_node* n = q->front; q->front; ) {
		q->front = q->front->next;
		free(n);
		n = q->front;
	}
}

Process* priority_queue_list_top(const Priority_queue_list* q)
{
	assert(q->front);
	return &q->front->p;
}

bool priority_queue_list_empty(const Priority_queue_list* q)
{
	return q->front == NULL;
}

void priority_queue_list_push(Priority_queue_list* q, const Process* x)
{
	Priority_queue_node* n = malloc(sizeof(Priority_queue_node));
	assert(n);
	n->p = *x;
	n->next = NULL;

	Priority_queue_node* prev = NULL;
	Priority_queue_node* current = q->front;
	while (current && (n->p.burst_time > current->p.burst_time || 
		(n->p.burst_time == current->p.burst_time &&
			n->p.arrival_time > current->p.arrival_time))) {
		prev = current;
		current = current->next;
	}
	if (!prev) {
		n->next = q->front;
		q->front = n;
	}
	else {
		prev->next = n;
		n->next = current;
	}
}

void priority_queue_list_pop(Priority_queue_list* q)
{
	if (q->front) {
		Priority_queue_node* n = q->front;
		q->front = q->front->next;
		free(n);
	}
}
