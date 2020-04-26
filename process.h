#include <sys/types.h>

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
