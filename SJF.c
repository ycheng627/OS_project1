#include "SJF.h"

int schedule_SJF(struct process* proc, int numProc) {
    int runnable = 0;
    int curTime = 0;
    struct process* running_p = NULL;

    struct priorityQ* pq = createpriorityQ();

    qsort(proc, numProc, sizeof(struct process), sjfcmpfunc);
    setCPU(getpid(), SCHEDULER_CPU);
    for (int i = 0; i < numProc; i++) {
        proc[i].pid = -1;
        proc[i].exist = 0;
        proc[i].active = 0;
    }
    /*
    push(pq, &proc[1]);
    push(pq, &proc[2]);
    push(pq, &proc[3]);
    push(pq, &proc[4]);
    push(pq, &proc[0]);

    while (!isEmpty(pq)) {
        struct process* tmp = pop(pq);
        printf("%s %d \n", tmp->name, tmp->exec_time);
    }*/

    while (1) {
        if (running_p != NULL && running_p->active == 1 && running_p->exec_time <= 0) {
            terminateProcess(running_p);
            if (runnable == numProc && isEmpty(pq)) {
                exit(0);
            }
            running_p = NULL;
        }

        while (runnable < numProc && proc[runnable].ready_time <= curTime) {
            push(pq, &proc[runnable]);
            childProcess(&proc[runnable]);
            minPriority(proc[runnable].pid);
            runnable++;
        }

        if (running_p == NULL && !isEmpty(pq)) {
            running_p = pop(pq);
            if (running_p->exist != 1) {
                childProcess(running_p);
                perror("child process spawning again");
            }
            maxPriority(running_p->pid);
            running_p->active = 1;
        }

        unitTime();
        if (running_p != NULL && running_p->active == 1) {
            running_p->exec_time--;
        }
        curTime++;
    }
}