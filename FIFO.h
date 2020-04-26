#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/types.h>

int fifocmpfunc(const void* a, const void* b) {
    return (((struct process*)a)->ready_time > ((struct process*)b)->ready_time);
}

int schedule_FIFO(struct process* proc, int numProc);