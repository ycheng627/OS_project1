#include "PSJF.h"

int schedule_PSJF(struct process* proc, int numProc) {
    int runnable = 0;
    int curTime = 0;
    struct process* running_p = NULL;

    struct priorityQ* pq = createpriorityQ();

    qsort(proc, numProc, sizeof(struct process), psjfcmpfunc);
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
                exit(0);
            }
            running_p = NULL;
        }

        while (runnable < numProc && proc[runnable].ready_time <= curTime) {
            push(pq, &proc[runnable]);
            childProcess(&proc[runnable]);
            minPriority(proc[runnable].pid);
            runnable++;

            //If the new process replace as the head
            if (running_p != NULL && running_p->exec_time > pq->front->proc->exec_time) {
                minPriority(running_p->pid);
                running_p->active = 0;
                push(pq, running_p);
                struct process* switch_p = pop(pq);
                switch_p->active = 1;
                maxPriority(switch_p->pid);
                running_p = switch_p;
            }
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

        if (running_p != NULL && running_p->active != 1) {
            if (kill(running_p->pid, 0) == 0) {  //To make sure pid still exist and prevent race condition
                maxPriority(running_p->pid);
            }
            running_p->active = 1;
            //reset to new running_p
        }

        unitTime();
        if (running_p != NULL && running_p->active == 1) {
            running_p->exec_time--;
        }
        curTime++;
    }
}