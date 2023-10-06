#pragma once

#include <stdio.h>

typedef struct process {
	int id;
	int arrival_time;
	int burst_time;
} Process;

void generate_processes(Process* p, int size, 
	int(*get_atime)(), int(*get_btime)());
void read_processes(FILE* stream, Process* p, int size);
void print_processes(FILE* stream, const Process* p, int size);

void sort_processes(Process* p, int size);