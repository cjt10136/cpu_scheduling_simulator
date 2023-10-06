#pragma once

#include "Queue_list.h"
#include "Queue_vector.h"
#include "Priority_queue_list.h"
#include "Priority_queue_vector.h"

typedef struct performance {
	double cpu_util;
	double throughput;
	double turnaround_time;
	double waiting_time;
	double response_time;
} Performance;

// First Come, First Serve
// Use Queue_list(Queue_vector)
void schedule_fcfs_listver(Performance* result, Process* data, int size);
void schedule_fcfs_vectorver(Performance* result, Process* data, int size);

// Round Robin
// Use Queue_list(Queue_vector)
void schedule_rr_listver(Performance* result, Process* data, int size);
void schedule_rr_vectorver(Performance* result, Process* data, int size);

// Shortest Job Next (Shortest Job First Non-Preemptive)
// Use Queue_list(Queue_vector) and Priority_queue_list(Priority_queue_vector)
void schedule_sjn_listver(Performance* result, Process* data, int size);
void schedule_sjn_vectorver(Performance* result, Process* data, int size);

// Shortest Remaining Time First (Shortest Job First Preemptive)
// Use Queue_list(Queue_vector) and Priority_queue_list(Priority_queue_vector)
void schedule_srtf_listver(Performance* result, Process* data, int size);
void schedule_srtf_vectorver(Performance* result, Process* data, int size);
