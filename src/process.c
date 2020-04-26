#define _GNU_SOURCE
#include "process.h"


int setCPU(pid_t pid, int cpuNum) {
    if (cpuNum > sizeof(cpu_set_t)) {
        perror("CPU index out of bounds");
        exit(1);
    }
    cpu_set_t mask;
	CPU_ZERO(&mask);
	CPU_SET(cpuNum, &mask);

    if (sched_setaffinity(pid, sizeof(mask), &mask)) {
		perror("sched_setaffinity error");
		exit(1);
	}
}

int maxPriority(pid_t pid){
    int max = sched_get_priority_max(SCHED_FIFO);
    struct sched_param parameter, test;
	parameter.sched_priority = max;

	if (sched_setscheduler(pid, SCHED_FIFO, &parameter)) {
		perror("sched_setscheduler error");
		exit(1);
	}
    sched_getparam(pid, &test);
    //printf("The priority after max priority is: %d", test);

}

int minPriority(pid_t pid){
    int min = sched_get_priority_min(SCHED_FIFO);
    struct sched_param parameter;
	parameter.sched_priority = min;

	if (sched_setscheduler(pid, SCHED_FIFO, &parameter)) {
		perror("sched_setscheduler error");
		exit(1);
	}

}

pid_t terminateProcess(struct process* proc){
    waitpid(proc->pid, NULL, 0);
    proc->exist = 0;
    proc->active = 0;
}

pid_t childProcess(struct process* proc){
    pid_t pid = fork();

    if (pid < 0){
        perror("fork error");
    }
    if (pid == 0){
        proc->pid = getpid();
        proc->exist = 1;
        setCPU(pid, FORK_CPU);
        minPriority(getpid());
        struct timespec start, end;
		syscall(GETTIME, &start, &start);
        
		for (int i = 0; i < proc->exec_time; i++) {
			unitTime();
#ifdef DEBUG
			if (i % 250 == 0)
				fprintf(stderr, "%s: %d/%d\n", proc->name, i, proc->exec_time);
#endif
		}
		syscall(GETTIME, &end);
        syscall(PRINTINFO, getpid(), start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
		exit(0);
    }
    else{
        setCPU(pid, FORK_CPU);
		minPriority(pid);
		proc->pid = pid;
		proc->exist = 1;

		printf("%s %d\n", proc->name, (int)proc->pid);
		fflush(stdout);
    }

}

