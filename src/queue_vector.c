#include "Queue_vector.h"

#include <assert.h>
#include <stdlib.h>

// Implementation interface
void queue_vector_reserve(Queue_vector* q, int new_cap);

void queue_vector_ctor(Queue_vector* q)
{
	q->begin = 0;
	q->end = 0;
	q->count = 0;
	q->capacity = 0;
	q->data = NULL;
}

void queue_vector_dtor(Queue_vector* q)
{
	free(q->data);
}

Process* queue_vector_top(const Queue_vector* q)
{
	assert(!queue_vector_empty(q));
	return &q->data[q->begin];
}

bool queue_vector_empty(const Queue_vector* q)
{
	return q->count == 0;
}

void queue_vector_push(Queue_vector* q, const Process* x)
{
	Process p = *x;
	if (q->count == q->capacity)
		queue_vector_reserve(q, 2 * q->capacity);
	q->data[q->end] = p;
	q->end = (q->end + 1) % q->capacity;
	++(q->count);
}

void queue_vector_pop(Queue_vector* q)
{
	assert(!queue_vector_empty(q));
	q->begin = (q->begin + 1) % q->capacity;
	--(q->count);
}

void queue_vector_reserve(Queue_vector* q, int new_cap)
{
	if (new_cap <= 0)
		new_cap = 1;
	Process* new_data = malloc(sizeof(Process) * new_cap);
	assert(new_data && new_cap > q->capacity);

	for (int i = 0; i < q->count; ++i)
		new_data[i] = q->data[(q->begin + i) % q->capacity];
	q->begin = 0;
	q->capacity = new_cap;
	q->end = (q->begin + q->count) % q->capacity;
	free(q->data);
	q->data = new_data;
}
