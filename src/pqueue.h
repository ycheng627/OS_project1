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

struct priorityQnode {
    struct process* proc;
    int priority;
    struct priorityQnode* next;
};

struct priorityQ {
    struct priorityQnode *front;
};

// A utility function to create a new linked list node.
struct priorityQnode* newNode(struct process* process);

// A utility function to create an empty priorityQ
struct priorityQ* createpriorityQ();

// The function to add a key k to q
void push(struct priorityQ* q, struct process* proc);

// Function to remove a key from given priorityQ q
struct process* pop(struct priorityQ* q);

int isEmpty(struct priorityQ* q);
