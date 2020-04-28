#include "FIFO.h"

int schedule_FIFO(struct process* proc, int numProc) {
    //int buf = bufferProc();
    int runnable = 0;
    int curTime = 0;
    int running = 0;

    qsort(proc, numProc, sizeof(struct process), fifocmpfunc);
    setCPU(getpid(), SCHEDULER_CPU);
    for (int i = 0; i < numProc; i++) {
        proc[i].pid = -1;
        proc[i].exist = 0;
        proc[i].active = 0;
    }
    while (1) {
        if (proc[running].active == 1 && proc[running].exec_time <= 0) {
            terminateProcess(&proc[running]);
            if (running == numProc - 1) {
                //kill(buf, 9);
                exit(0);
            }
            running++;
        }

        while (runnable < numProc && proc[runnable].ready_time <= curTime) {
            childProcess(&proc[runnable]);
            //printf("The %d pid is: %d\n", runnable, proc[runnable].pid);
            minPriority(proc[runnable].pid);  //new process should not execute yet
            runnable++;
        }

        if (proc[running].exist == 1 && proc[running].active == 0) {
            //printf("the pid for running %d is %s %d\n", running, proc[running].name,  proc[running].pid);
            maxPriority(proc[running].pid);
            proc[running].active = 1;
        }

#ifdef DEBUG
        /*if (curTime % 500 == 0) {
            printf("Current Running: %d current finished\n", running);
        }*/
#endif
        unitTime();
        if (proc[running].active == 1) {
            proc[running].exec_time--;
        }
        curTime++;
    }

    return 1;
}