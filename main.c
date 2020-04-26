#define _GNU_SOURCE
#include "process.h"
#include "scheduler.h"
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]) {
    char policyStr[256];
    int policy;
    int numProc;
    scanf("%s", policyStr);
    scanf("%d", &numProc);
    struct process* proc = (struct process*)malloc(sizeof(struct process) * numProc);

    for (int i = 0; i < numProc; i++) {
        scanf("%s %d %d", proc[i].name, &(proc[i].ready_time), &(proc[i].exec_time));
    }

#ifdef DEBUG
    /*printf("%s\n%d\n", policyStr, numProc);
    for (int i = 0; i < numProc; i++) {
        printf("%s %d %d\n", proc[i].name, proc[i].ready_time, proc[i].exec_time);
    }*/
#endif

    if (strcmp(policyStr, "FIFO") == 0) {
        schedule_FIFO(proc, numProc);
    } else if (strcmp(policyStr, "RR") == 0) {
        schedule_RR(proc, numProc);
    } else if (strcmp(policyStr, "SJF") == 0) {
        schedule_SJF(proc, numProc);
    } else if (strcmp(policyStr, "PSJF") == 0) {
        //policy = PSJF;
    } else {
        perror("unrecognized policy");
    }

    //schedule(policy, proc, numProc);

    return 0;
}