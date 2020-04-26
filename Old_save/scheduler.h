#ifndef _SCHEDULING_H_
#define _SCHEDULING_H_
#include <sys/types.h>

#define FIFO 1
#define RR 2
#define SJF 3
#define PSJF 4
#define ll long long

#define unitTime()                      \
    {                                   \
        volatile unsigned long z;       \
        for (z = 0; z < 1000000UL; z++) \
            ;                           \
    }                                   \
    //choose z to make sure no accidental naming problem \
    //use define to prevent function call overhead from timing

int schedule(int policy, struct process* proc, int numProc);

#endif