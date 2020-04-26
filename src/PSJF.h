#define _GNU_SOURCE
#include "pqueue.h"

int psjfcmpfunc(const void* a, const void* b) {
    return (((struct process*)a)->ready_time > ((struct process*)b)->ready_time);
}

int schedule_PSJF(struct process* proc, int numProc);

