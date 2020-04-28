#include "RR.h"

int schedule_RR(struct process* proc, int numProc) {
    int buf = bufferProc();
    int switchTime = ROUNDTIME;
    int curTime = 0;
    int runnable = 0;

    struct Queue* q = createQueue();
    qsort(proc, numProc, sizeof(struct process), rrcmpfunc);
    setCPU(getpid(), SCHEDULER_CPU);
    maxPriority(getpid());
    for (int i = 0; i < numProc; i++) {
        proc[i].pid = -1;
        proc[i].exist = 0;
        proc[i].active = 0;
    }
    struct process* running_p;
    while (1) {
        if (running_p == NULL && q->front != NULL) {
            running_p = q->front->proc;
            switchTime = ROUNDTIME;
            //fprintf(stderr, "got something");
        }
        while (runnable < numProc && proc[runnable].ready_time <= curTime) {
            childProcess(&proc[runnable]);
            minPriority(proc[runnable].pid);
            enQueue(q, &proc[runnable]);
            //fprintf(stderr, "enqueueing: %d\n", runnable);
            runnable++;
#ifdef DEBUG
            fprintf(stderr, "adding new Process %d at time %d\n", runnable, curTime - 1200);
#endif
        }

        if (running_p != NULL && running_p->active == 1 && running_p->exec_time <= 0) {
#ifdef DEBUG
            fprintf(stderr, "terminating %s at time %d\n", running_p->name, curTime - 1200);
#endif
            deQueue(q);  //get it out of the queue now that it is done
            //fprintf(stderr, "dequeueing: %s\n", running_p->name);
            terminateProcess(running_p);

            if (runnable == numProc && isEmptyQueue(q)) {
                kill(buf, 9);
                exit(0);
            }
            running_p = NULL;
        }

        if (switchTime <= 0) {
            if (running_p != NULL && running_p->active == 1) {
                if (kill(running_p->pid, 0) == 0) {  //To make sure pid still exist and prevent race condition
                    minPriority(running_p->pid);
                }
                running_p->active = 0;
                deQueue(q);
                //fprintf(stderr, "switching, dequeuing this: %s\n", running_p->name);
                //printf("top now is: %s\n", q->front->proc->name);
                enQueue(q, running_p);
                //fprintf(stderr, "switching, enqueuing this: %s\n", running_p->name);
                switchTime = ROUNDTIME;
                running_p = NULL;
            }
        }

        if (running_p != NULL && running_p->active != 1) {
            if (kill(running_p->pid, 0) == 0) {  //To make sure pid still exist and prevent race condition
                //perror("changing to max");
                maxPriority(running_p->pid);
            }
            running_p->active = 1;
            //reset to new running_p
        }

        if (curTime % 100 == 0) {
            //fprintf(stderr, "curTime: %d\n", curTime);
        }
        unitTime();
        if (running_p != NULL && running_p->active == 1) {
            running_p->exec_time--;
            switchTime--;
        }
        curTime++;
    }
}