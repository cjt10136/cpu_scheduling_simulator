#include "Queue_list.h"

#include <assert.h>
#include <stdlib.h>

void queue_list_ctor(Queue_list* q)
{
	q->front = NULL;
	q->back = NULL;
}

void queue_list_dtor(Queue_list* q)
{
	for (Queue_node* n = q->front; q->front; ) {
		q->front = q->front->next;
		free(n);
		n = q->front;
	}
}

Process* queue_list_top(const Queue_list* q)
{
	assert(q->front);
	return &q->front->p;
}

bool queue_list_empty(const Queue_list* q)
{
	return q->front == NULL;
}

void queue_list_push(Queue_list* q, const Process* x)
{
	Queue_node* n = malloc(sizeof(Queue_node));
	assert(n);
	n->p = *x;
	n->next = NULL;
	if (q->back) {
		q->back->next = n;
		q->back = n;
	}
	else {
		q->front = n;
		q->back = n;
	}
}

void queue_list_pop(Queue_list* q)
{
	if (q->front) {
		Queue_node* n = q->front;
		q->front = q->front->next;
		free(n);
		if (!q->front)
			q->back = NULL;
	}
}
