#include "Process.h"

#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Implementation interface
int compare_processes(const void* a, const void* b);

int compare_processes(const void* a, const void* b)
{
	const Process* p1 = (const Process*)a;
	const Process* p2 = (const Process*)b;
	return (p1->arrival_time > p2->arrival_time ||
		(p1->arrival_time == p2->arrival_time && p1->burst_time > p2->burst_time)) -
		(p1->arrival_time < p2->arrival_time);
}

void generate_processes(Process* p, int size,
	int(*get_atime)(), int(*get_btime)())
{
    srand(time(NULL));
	for (int i = 0; i < size; ++i) {
		p[i].id = i + 1;
		p[i].arrival_time = get_atime();
		p[i].burst_time = get_btime();
	}
}

void read_processes(FILE* stream, Process* p, int size)
{
	for (int i = 0; i < size; ++i) {
		p[i].id = i + 1;
		fscanf(stream, "%d", &p[i].arrival_time);
	}
	for (int i = 0; i < size; ++i)
		fscanf(stream, "%d", &p[i].burst_time);
}

void print_processes(FILE* stream, const Process* p, int size)
{
	fprintf(stream, " ID| Arrival Time| Burst Time|\n");
	for (int i = 0; i < size; ++i)
		fprintf(stream, "%3d|%13d|%11d|\n", 
			p[i].id, p[i].arrival_time, p[i].burst_time);
}

 void print_queue(FILE* stream, Process* p, int size)
 {
 	fprintf(stream, "Time          : |");
 	for (int i = 0; i < 1000; ++i)
 		fprintf(stream, "  %03d  |", i);
 	fprintf(stream, "\n");
 
 	int mx = 1;
 	int* lengths = malloc(sizeof(int) * size);
 	for (int begin = 0; begin < size; ) {
 		int end = begin + 1;
 		while (end < size && p[end].arrival_time == p[end - 1].arrival_time)
 			++end;
 		lengths[begin] = end - begin;
 		if (end - begin > mx)
 			mx = end - begin;
 		begin = end;
 	}
 
 	char** lines = malloc(sizeof(char*) * mx);
 	for (int i = 0; i < mx; ++i)
 		*(lines + i) = malloc(sizeof(char) * 8 * 1000);
 	
 	sprintf(*lines, "ID(Burst Time): |");
 	for (int i = 1; i < mx; ++i)
 		sprintf(*(lines + i), "                |");
 	for (int j = 0; j < lengths[0]; ++j) {
 		for (int k = 0; k < p[0].arrival_time; ++k)
 			sprintf(*(lines + j) + strlen(*(lines + j)), "       |");
 		sprintf(*(lines + j) + strlen(*(lines + j)),
 			"%3d(%2d)|", p[j].id, p[j].burst_time);
 	}
 	for (int j = lengths[0]; j < mx; ++j) {
 		for (int k = 0; k < p[0].arrival_time + 1; ++k)
 			sprintf(*(lines + j) + strlen(*(lines + j)), "       |");
 	}
 	for (int i = lengths[0]; i < size; i += lengths[i]) {
 		for (int j = 0; j < lengths[i]; ++j) {
 			for (int k = 0; k < p[i].arrival_time - p[i - 1].arrival_time - 1; ++k)
 				sprintf(*(lines + j) + strlen(*(lines + j)), "       |");
 			sprintf(*(lines + j) + strlen(*(lines + j)),
 				"%3d(%2d)|", p[i + j].id, p[i + j].burst_time);
 			
 		}
 		for (int j = lengths[i]; j < mx; ++j) {
 			for (int k = 0; k < p[i].arrival_time - p[i - 1].arrival_time; ++k)
 				sprintf(*(lines + j) + strlen(*(lines + j)), "       |");
 		}
 	}
 	for (int i = 0; i < mx; ++i)
 		fprintf(stream, "%s\n", *(lines + i));
 }

void sort_processes(Process* p, int size)
{
	qsort(p, size, sizeof(Process), compare_processes);
}
