#include "scheduling.h"

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>

#define RR_TIME_QUANTUM 4

void schedule_fcfs_listver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_list job_queue;
	queue_list_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_list_push(&job_queue, &data[i]);
	Queue_list ready_queue;
	queue_list_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	int time = 1;
	while (!(queue_list_empty(&job_queue) && queue_list_empty(&ready_queue))) {
		while (!queue_list_empty(&job_queue) &&
			queue_list_top(&job_queue)->arrival_time < time) {
			Process* p = queue_list_top(&job_queue);
			result->waiting_time += p->burst_time;
			queue_list_push(&ready_queue, p);
			queue_list_pop(&job_queue);
		}

		if (!queue_list_empty(&ready_queue)) {
			++(result->cpu_util);
			Process* p = queue_list_top(&ready_queue);
			--(p->burst_time);
			if (!visited[p->id - 1]) {
				visited[p->id - 1] = true;
				result->response_time += time - 1 - p->arrival_time;
			}
			if (p->burst_time == 0) {
				result->turnaround_time += time - p->arrival_time;
				queue_list_pop(&ready_queue);
			}
		}
		++time;
	}

	queue_list_dtor(&job_queue);
	queue_list_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}

void schedule_fcfs_vectorver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_vector job_queue;
	queue_vector_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_vector_push(&job_queue, &data[i]);
	Queue_vector ready_queue;
	queue_vector_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	int time = 1;
	for (; !(queue_vector_empty(&job_queue)
		&& queue_vector_empty(&ready_queue)); ++time) {
		while (!queue_vector_empty(&job_queue) &&
			queue_vector_top(&job_queue)->arrival_time < time) {
			Process* p = queue_vector_top(&job_queue);
			result->waiting_time += p->burst_time;
			queue_vector_push(&ready_queue, p);
			queue_vector_pop(&job_queue);
		}

		if (!queue_vector_empty(&ready_queue)) {
			++(result->cpu_util);
			Process* p = queue_vector_top(&ready_queue);
			--(p->burst_time);
			if (!visited[p->id - 1]) {
				visited[p->id - 1] = true;
				result->response_time += time - 1 - p->arrival_time;
			}
			if (p->burst_time == 0) {
				result->turnaround_time += time - p->arrival_time;
				queue_vector_pop(&ready_queue);
			}
		}
	}

	queue_vector_dtor(&job_queue);
	queue_vector_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}

void schedule_rr_listver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_list job_queue;
	queue_list_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_list_push(&job_queue, &data[i]);
	Queue_list ready_queue;
	queue_list_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	int stop_watch = 0;
	int time = 1;
	for (; !(queue_list_empty(&job_queue)
		&& queue_list_empty(&ready_queue)); ++time) {
		while (!queue_list_empty(&job_queue) &&
			queue_list_top(&job_queue)->arrival_time < time) {
			Process* p = queue_list_top(&job_queue);
			result->waiting_time += p->burst_time;
			queue_list_push(&ready_queue, p);
			queue_list_pop(&job_queue);
		}

		if (!queue_list_empty(&ready_queue)) {
			Process* p = queue_list_top(&ready_queue);
			if (stop_watch == RR_TIME_QUANTUM) {
				queue_list_push(&ready_queue, p);
				queue_list_pop(&ready_queue);
				stop_watch = 0;
				p = queue_list_top(&ready_queue);
			}
			++stop_watch;
			++(result->cpu_util);
			--(p->burst_time);
			if (!visited[p->id - 1]) {
				visited[p->id - 1] = true;
				result->response_time += time - 1 - p->arrival_time;
			}
			if (p->burst_time == 0) {
				result->turnaround_time += time - p->arrival_time;
				queue_list_pop(&ready_queue);
				stop_watch = 0;
			}
		}
	}

	queue_list_dtor(&job_queue);
	queue_list_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}

void schedule_rr_vectorver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_vector job_queue;
	queue_vector_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_vector_push(&job_queue, &data[i]);
	Queue_vector ready_queue;
	queue_vector_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	int stop_watch = 0;
	int time = 1;
	for (; !(queue_vector_empty(&job_queue)
		&& queue_vector_empty(&ready_queue)); ++time) {
		while (!queue_vector_empty(&job_queue) &&
			queue_vector_top(&job_queue)->arrival_time < time) {
			Process* p = queue_vector_top(&job_queue);
			result->waiting_time += p->burst_time;
			queue_vector_push(&ready_queue, p);
			queue_vector_pop(&job_queue);
		}

		if (!queue_vector_empty(&ready_queue)) {
			Process* p = queue_vector_top(&ready_queue);
			if (stop_watch == RR_TIME_QUANTUM) {
				queue_vector_push(&ready_queue, p);
				queue_vector_pop(&ready_queue);
				stop_watch = 0;
				p = queue_vector_top(&ready_queue);
			}
			++stop_watch;
			++(result->cpu_util);
			--(p->burst_time);
			if (!visited[p->id - 1]) {
				visited[p->id - 1] = true;
				result->response_time += time - 1 - p->arrival_time;
			}
			if (p->burst_time == 0) {
				result->turnaround_time += time - p->arrival_time;
				queue_vector_pop(&ready_queue);
				stop_watch = 0;
			}
		}
	}

	queue_vector_dtor(&job_queue);
	queue_vector_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}

void schedule_sjn_listver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_list job_queue;
	queue_list_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_list_push(&job_queue, &data[i]);
	Priority_queue_list ready_queue;
	priority_queue_list_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	Process temp;
	Process* current = NULL;
	int time = 1;
	for (; !queue_list_empty(&job_queue) ||
		!priority_queue_list_empty(&ready_queue) || current; ++time) {
		while (!queue_list_empty(&job_queue) &&
			queue_list_top(&job_queue)->arrival_time < time) {
			Process* p = queue_list_top(&job_queue);
			result->waiting_time += p->burst_time;
			priority_queue_list_push(&ready_queue, p);
			queue_list_pop(&job_queue);
		}

		if (!priority_queue_list_empty(&ready_queue) || current) {
			++(result->cpu_util);
			if (!current) {
				temp = *(priority_queue_list_top(&ready_queue));
				current = &temp;
				priority_queue_list_pop(&ready_queue);
			}
			--(current->burst_time);
			if (!visited[current->id - 1]) {
				visited[current->id - 1] = true;
				result->response_time += time - 1 - current->arrival_time;
			}
			if (current->burst_time == 0) {
				result->turnaround_time += time - current->arrival_time;
				current = NULL;
			}
		}
	}

	queue_list_dtor(&job_queue);
	priority_queue_list_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}

void schedule_sjn_vectorver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_vector job_queue;
	queue_vector_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_vector_push(&job_queue, &data[i]);
	Priority_queue_vector ready_queue;
	priority_queue_vector_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	Process temp;
	Process* current = NULL;
	int time = 1;
	for (; !queue_vector_empty(&job_queue) ||
		!priority_queue_vector_empty(&ready_queue) || current; ++time) {
		while (!queue_vector_empty(&job_queue) &&
			queue_vector_top(&job_queue)->arrival_time < time) {
			Process* p = queue_vector_top(&job_queue);
			result->waiting_time += p->burst_time;
			priority_queue_vector_push(&ready_queue, p);
			queue_vector_pop(&job_queue);
		}

		if (!priority_queue_vector_empty(&ready_queue) || current) {
			++(result->cpu_util);
			if (!current) {
				temp = *(priority_queue_vector_top(&ready_queue));
				current = &temp;
				priority_queue_vector_pop(&ready_queue);
			}
			--(current->burst_time);
			if (!visited[current->id - 1]) {
				visited[current->id - 1] = true;
				result->response_time += time - 1 - current->arrival_time;
			}
			if (current->burst_time == 0) {
				result->turnaround_time += time - current->arrival_time;
				current = NULL;
			}
		}
	}

	queue_vector_dtor(&job_queue);
	priority_queue_vector_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}

void schedule_srtf_listver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_list job_queue;
	queue_list_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_list_push(&job_queue, &data[i]);
	Priority_queue_list ready_queue;
	priority_queue_list_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	int time = 1;
	for (; !(queue_list_empty(&job_queue)
		&& priority_queue_list_empty(&ready_queue)); ++time) {
		while (!queue_list_empty(&job_queue) &&
			queue_list_top(&job_queue)->arrival_time < time) {
			Process* p = queue_list_top(&job_queue);
			result->waiting_time += p->burst_time;
			priority_queue_list_push(&ready_queue, p);
			queue_list_pop(&job_queue);
		}

		if (!priority_queue_list_empty(&ready_queue)) {
			++(result->cpu_util);
			Process* p = priority_queue_list_top(&ready_queue);
			--(p->burst_time);
			if (!visited[p->id - 1]) {
				visited[p->id - 1] = true;
				result->response_time += time - 1 - p->arrival_time;
			}
			if (p->burst_time == 0) {
				result->turnaround_time += time - p->arrival_time;
				priority_queue_list_pop(&ready_queue);
			}
		}
	}

	queue_list_dtor(&job_queue);
	priority_queue_list_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}

void schedule_srtf_vectorver(Performance* result, Process* data, int size)
{
	result->cpu_util = 0.0;
	result->throughput = 0.0;
	result->turnaround_time = 0.0;
	result->waiting_time = 0.0;
	result->response_time = 0.0;

	Queue_vector job_queue;
	queue_vector_ctor(&job_queue);
	for (int i = 0; i < size; ++i)
		queue_vector_push(&job_queue, &data[i]);
	Priority_queue_vector ready_queue;
	priority_queue_vector_ctor(&ready_queue);

	// record whether a process has been processed before so as to calculate
	// the response time
	bool* visited = calloc(size, sizeof(bool));
	assert(visited);
	int time = 1;
	for (; !(queue_vector_empty(&job_queue)
		&& priority_queue_vector_empty(&ready_queue)); ++time) {
		while (!queue_vector_empty(&job_queue) &&
			queue_vector_top(&job_queue)->arrival_time < time) {
			Process* p = queue_vector_top(&job_queue);
			result->waiting_time += p->burst_time;
			priority_queue_vector_push(&ready_queue, p);
			queue_vector_pop(&job_queue);
		}

		if (!priority_queue_vector_empty(&ready_queue)) {
			++(result->cpu_util);
			Process* p = priority_queue_vector_top(&ready_queue);
			--(p->burst_time);
			if (!visited[p->id - 1]) {
				visited[p->id - 1] = true;
				result->response_time += time - 1 - p->arrival_time;
			}
			if (p->burst_time == 0) {
				result->turnaround_time += time - p->arrival_time;
				priority_queue_vector_pop(&ready_queue);
			}
		}
	}

	queue_vector_dtor(&job_queue);
	priority_queue_vector_dtor(&ready_queue);

	result->cpu_util /= (time - 1);
	result->throughput = (double)size / (time - 1);
	result->turnaround_time /= size;
	result->waiting_time = result->turnaround_time - result->waiting_time / size;
	result->response_time /= size;
}
