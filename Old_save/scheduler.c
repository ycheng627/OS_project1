#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int curTime = 0;
int rr_lastSwitch = 0;
int finished_cnt = 0;
int running = -1;

int nextProcess(int policy, struct process* proc, int numProc) {  //return the id in proc for the next process (can be same continued) to be executed
    if (policy == FIFO) {
        if (running != -1) {
            fprintf(stderr, "return same cuz running\n");
            return running;
        } else {
            int ret = -1;
            for (int i = 0; i < numProc; i++) {
                if (proc[i].pid != -1 && proc[i].exec_time > 0 && ret == -1) {
                    ret = proc[i].pid;
                }
            }
            return ret;
        }
    }
}

int cmpfunc(const void* a, const void* b) {
    return (((struct process*)a)->ready_time > ((struct process*)b)->ready_time);
}

int schedule(int policy, struct process* proc, int numProc) {
    qsort(proc, numProc, sizeof(struct process), cmpfunc);
    setCPU(getpid(), SCHEDULER_CPU);
    maxPriority(getpid());
#ifdef DEBUG
    for (int i = 0; i < 1; i++) {
        unitTime();
    }

    for (int i = 0; i < numProc; i++) {
        printf("Process: %s ready time: %d\n", proc[i].name, proc[i].ready_time);
    }
#endif
    for (int i = 0; i < numProc; i++) {
        proc[i].pid = -1;
    }

    while (finished_cnt < numProc) {
        for (int i = 0; i < numProc; i++) {
            if (curTime == proc[i].ready_time) {
                proc[i].pid = childProcess(&proc[i]);
                minPriority(proc[i].pid);  //new process should not execute yet
            }
        }
        if (proc[running].exec_time == 0) {
            wait(NULL);
            running = -1;
            finished_cnt++;
            printf("cnt: %d\n", finished_cnt);
        }
        if (curTime % 500 == 0){
            printf(stderr, "\nCurrent Running: %d current finished: %d\n", running, finished_cnt);
        }
        int nextP = nextProcess(policy, proc, numProc);
        fprintf(stderr, "next process is %d\n", nextP);
        if (running != nextP) {
            if (running != -1) {
                minPriority(running);
            }
            running = nextP;
            if (running != -1) {
                maxPriority(running);   
            }
        }

        proc[running].exec_time--;
        curTime++;
    }

    return 1;
}

/*
    sort by ready time, to know who to add next
    Make sure scheduler is in the correct CPU and priority
    init proc PID
    record number of finished process
    record whether there is currently a process running
    enter while loop
        if ready time is met, create child process and assign proc ID (new process at low priority first)
        Check if the current running process is done
            if done, wait() it
            print start and end (actually, do this in the child process)
            set running to -1 to indicate no current process
            finished ++
        Call next process
            if next process != current process (running)
                if running != -1 //-1 means that no one is running
                    set running priority low
                    set next priority high
                    RR_startTime = curTime; //use this value to check when to context switch out
            if next process == -1
                exit
        if finished count = n
            exit
        wait unit time
        if (running != -1)
            proc[runninf].exec_time --
        time ++;
    For each possible 


    */
