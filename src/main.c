#define USE_GET_FUNCTIONS
#define SIZE_OF_PROCESSES 200

#include "scheduling.h"

#include <stdio.h>
#include <stdlib.h>

#ifdef USE_GET_FUNCTIONS
int get_arrival_time()
{
	return rand() % 1000;
}

int get_burst_time()
{
	return rand() % 8 + 1;
}
#endif // USE_GET_FUNCTIONS

int main(void)
{
	Process p[SIZE_OF_PROCESSES];
#ifndef USE_GET_FUNCTIONS
	FILE* fp = fopen("input.txt", "r");
	if (!fp)
		return;
	read_processes(fp, p, SIZE_OF_PROCESSES);
	fclose(fp);
#else
	generate_processes(p, SIZE_OF_PROCESSES, &get_arrival_time, &get_burst_time);
#endif // USE_GET_FUNCTIONS

	sort_processes(p, SIZE_OF_PROCESSES);
	print_processes(stdout, p, SIZE_OF_PROCESSES);
	puts("\n");

	Performance result;
	puts("***************First Come, First Serve Scheduling***************");
	puts("Linked List Version");
	schedule_fcfs_listver(&result, p, SIZE_OF_PROCESSES);
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n\n", result.response_time);

	puts("Array Version");
	schedule_fcfs_vectorver(&result, p, SIZE_OF_PROCESSES);
	puts("First Come, First Serve Scheduling:");
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n", result.response_time);
	puts("***************First Come, First Serve Scheduling***************\n\n");

	puts("*********************Round Robin Scheduling*********************");
	schedule_rr_listver(&result, p, SIZE_OF_PROCESSES);
	puts("Linked List Version");
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n\n", result.response_time);

	schedule_rr_vectorver(&result, p, SIZE_OF_PROCESSES);
	puts("Array Version");
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n", result.response_time);
	puts("*********************Round Robin Scheduling*********************\n\n");

	puts("******************Shortest Job Next Scheduling******************");
	puts("Linked List Version");
	schedule_sjn_listver(&result, p, SIZE_OF_PROCESSES);
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n\n", result.response_time);

	puts("Array Version");
	schedule_sjn_vectorver(&result, p, SIZE_OF_PROCESSES);
	puts("First Come, First Serve Scheduling:");
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n", result.response_time);
	puts("******************Shortest Job Next Scheduling******************\n\n");
	
	puts("************Shortest Remaining Time First Scheduling************");
	puts("Linked List Version");
	schedule_srtf_listver(&result, p, SIZE_OF_PROCESSES);
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n\n", result.response_time);

	puts("Array Version");
	schedule_srtf_vectorver(&result, p, SIZE_OF_PROCESSES);
	puts("First Come, First Serve Scheduling:");
	printf("CPU Utilization: %.4lf\n", result.cpu_util);
	printf("Throughput     : %.4lf\n", result.throughput);
	printf("Turnaround Time: %.4lf\n", result.turnaround_time);
	printf("Waiting Time   : %.4lf\n", result.waiting_time);
	printf("Response Time  : %.4lf\n", result.response_time);
	puts("************Shortest Remaining Time First Scheduling************\n\n");
}
