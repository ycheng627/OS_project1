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

int maxPriority(pid_t pid) {
    /*int which = PRIO_PROCESS;
    int priority = -20; //max, but not -20 just in case
    setpriority(which, pid, priority);*/

    //int max = sched_get_priority_max(SCHED_FIFO);

    int max = 90;
    struct sched_param parameter, test;
    parameter.sched_priority = max;

    if (sched_setscheduler(pid, SCHED_FIFO, &parameter)) {
        perror("sched_setscheduler error");
        exit(1);
    }
    sched_getparam(pid, &test);
    //perror("set max priority");
    //printf("The priority after max priority is: %d", test);
}

int medPriority(pid_t pid) {
    struct sched_param param;
    param.sched_priority = 0;
    if (sched_setscheduler(pid, SCHED_OTHER, &param) != 0)
        exit(1);
    nice(-20);
}

int minPriority(pid_t pid) {
    struct sched_param param;
    param.sched_priority = 0;
    if (sched_setscheduler(pid, SCHED_OTHER, &param) != 0)
        exit(1);
    
    
    /*int min = sched_get_priority_min(SCHED_FIFO);
    struct sched_param parameter;
    parameter.sched_priority = min;

    if (sched_setscheduler(pid, SCHED_FIFO, &parameter)) {
        perror("sched_setscheduler error");
        exit(1);
    }*/
}

int bufferProc() {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
    }
    if (pid == 0) {
        setCPU(getpid(), FORK_CPU);
        medPriority(getpid());
        //nice(-10); // better than normal
        //perror("created dummy");
        
        //while(1);
        int k = 0;
        for (volatile j = 0; j > -1; j = j + 1 % 1000) {  //a while loop that won't be optimized?
            unitTime();
            k = k + 1 % 100;
            if (j % 50 == 0) {
               //perror("buffering");
            }
        }

        exit(0);
    } else {
        setCPU(pid, FORK_CPU);
        medPriority(pid);
        //nice(-10); // better than normal
        //perror("returning");
        return pid;
    }
}

pid_t terminateProcess(struct process* proc) {
    waitpid(proc->pid, NULL, 0);
    proc->exist = 0;
    proc->active = 0;
}

pid_t childProcess(struct process* proc) {
    pid_t pid = fork();

    if (pid < 0) {
        perror("fork error");
    }
    if (pid == 0) {
        proc->pid = getpid();
        //topPriority(getpid());
        proc->exist = 1;
        //setCPU(getpid(), FORK_CPU);
        //minPriority(getpid());
        sched_yield();
        for (int i = 0; i < 20; i++) {
            unitTime();
        }
        //unitTime();
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
    } else {
        setCPU(pid, FORK_CPU);
        minPriority(pid);
        proc->pid = pid;
        proc->exist = 1;

        printf("%s %d\n", proc->name, (int)proc->pid);
        fflush(stdout);
    }
}
