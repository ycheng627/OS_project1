#include <sys/types.h>
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>

#define unitTime()                      \
    {                                   \
        volatile unsigned long z;       \
        for (z = 0; z < 1000000UL; z++) \
            ;                           \
    }                                   \
    //choose z to make sure no accidental naming problem \
    //use define to prevent function call overhead from timing


#define FORK_CPU 1
#define SCHEDULER_CPU 0
//Will try to time by executing on different CPU and counting how long has passed

#define GETTIME 333
#define PRINTINFO 334

struct process {
	char name[32];
	int ready_time;
	int exec_time;
	pid_t pid;
    int active;
    int exist;
};

int setCPU(pid_t pid, int cpuNum);
int maxPriority(pid_t pid);
int minPriority(pid_t pid);
pid_t terminateProcess(struct process* proc);
pid_t childProcess(struct process* proc);
