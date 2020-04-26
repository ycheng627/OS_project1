#define _GNU_SOURCE
#include "queue.h"
#define ROUNDTIME 500

int rrcmpfunc(const void* a, const void* b) {
    return (((struct process*)a)->ready_time > ((struct process*)b)->ready_time);
}

int schedule_RR(struct process* proc, int numProc);

