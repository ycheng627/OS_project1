#define _GNU_SOURCE
#include "process.h"
#include <errno.h>
#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysinfo.h>
#include <unistd.h>
#include <sys/types.h>

//Queue code taken and modified from geeksforgeeks

struct QNode {
    struct process* proc;
    struct QNode* next;
};

struct Queue {
    struct QNode *front, *rear;
};

// A utility function to create a new linked list node.
struct QNode* newQueueNode(struct process* process);
// A utility function to create an empty queue
struct Queue* createQueue();

// The function to add a key k to q
void enQueue(struct Queue* q, struct process* proc);

// Function to remove a key from given queue q
void deQueue(struct Queue* q);

int isEmptyQueue(struct Queue* q);