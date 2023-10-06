#include "Priority_queue_vector.h"

#include <assert.h>
#include <stdlib.h>

// Implementation interface
void priority_queue_vector_reserve(Priority_queue_vector* q, int new_cap);

void priority_queue_vector_ctor(Priority_queue_vector* q)
{
	q->end = 0;
	q->capacity = 0;
	q->data = NULL;
}

void priority_queue_vector_dtor(Priority_queue_vector* q)
{
	free(q->data);
}

Process* priority_queue_vector_top(const Priority_queue_vector* q)
{
	assert(q->end != 0);
	return &q->data[0];
}

bool priority_queue_vector_empty(const Priority_queue_vector* q)
{
	return q->end == 0;
}

void priority_queue_vector_push(Priority_queue_vector* q, const Process* x)
{
	if (q->end == q->capacity)
		priority_queue_vector_reserve(q, 2 * q->capacity);
	q->data[q->end] = *x;
	++(q->end);

	int down = q->end - 1;
	int up = (down - 1) / 2;
	while (up >= 0 && q->data[down].burst_time < q->data[up].burst_time) {
		Process temp = q->data[down];
		q->data[down] = q->data[up];
		q->data[up] = temp;
		down = up;
		up = (down - 1) / 2;
	}
}

void priority_queue_vector_pop(Priority_queue_vector* q)
{
	assert(q->end > 0);
	q->data[0] = q->data[q->end - 1];
	--(q->end);

	int up = 0;
	int left = 1;
	int right = 2;

	int mn;
	if (left < q->end && q->data[left].burst_time < q->data[up].burst_time)
		mn = left;
	else
		mn = up;
	if (right < q->end && q->data[right].burst_time < q->data[mn].burst_time)
		mn = right;

	while (mn != up) {
		Process temp = q->data[up];
		q->data[up] = q->data[mn];
		q->data[mn] = temp;

		up = mn;
		left = 2 * (up + 1) - 1;
		right = 2 * (up + 1);
		if (left < q->end && q->data[left].burst_time < q->data[up].burst_time)
			mn = left;
		else
			mn = up;
		if (right < q->end && q->data[right].burst_time < q->data[mn].burst_time)
			mn = right;
	}
}

void priority_queue_vector_reserve(Priority_queue_vector* q, int new_cap)
{
	if (new_cap <= 0)
		new_cap = 1;
	Process* new_data = malloc(sizeof(Process) * new_cap);
	assert(new_data && new_cap >= q->capacity);

	for (int i = 0; i < q->end; ++i)
		new_data[i] = q->data[i];
	q->capacity = new_cap;
	free(q->data);
	q->data = new_data;
}
