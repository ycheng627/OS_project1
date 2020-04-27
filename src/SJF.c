#include "SJF.h"

int schedule_SJF(struct process* proc, int numProc) {
    //int buf = bufferProc();
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

    while (1) {
        if (running_p != NULL && running_p->active == 1 && running_p->exec_time <= 0) {
            terminateProcess(running_p);
            if (runnable == numProc && isEmpty(pq)) {
                //kill(buf, 9);
                exit(0);
            }
            running_p = NULL;
        }

        if (running_p == NULL && !isEmpty(pq)) {
            running_p = pop(pq);
            if (running_p->exist != 1) {
                childProcess(running_p);
                //perror("child process spawning again");
            }
            maxPriority(running_p->pid);
            running_p->active = 1;
        }

        while (runnable < numProc && proc[runnable].ready_time <= curTime) {
            push(pq, &proc[runnable]);
            childProcess(&proc[runnable]);
            minPriority(proc[runnable].pid);
            runnable++;
        }

        unitTime();
        if (running_p != NULL && running_p->active == 1) {
            running_p->exec_time--;
        }
        curTime++;
    }
}