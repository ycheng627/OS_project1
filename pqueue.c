#include "pqueue.h"

// A utility function to create a new linked list node.
struct priorityQnode* newNode(struct process* process) {
    struct priorityQnode* temp = (struct priorityQnode*)malloc(sizeof(struct priorityQnode));
    temp->proc = process;
    temp->priority = process->exec_time;
    temp->next = NULL;
    return temp;
}

// A utility function to create an empty priorityQ
struct priorityQ* createpriorityQ() {
    struct priorityQ* priorityQueue = (struct priorityQ*)malloc(sizeof(struct priorityQ));
    priorityQueue->front = NULL;
    return priorityQueue;
}

// The function to add a key k to q
void push(struct priorityQ* q, struct process* proc) {
    // Create a new LL node
    struct priorityQnode* temp = newNode(proc);

    // If priorityQ is empty, then new node is front and rear both
    if (q->front == NULL) {
        q->front = temp;
        return;
    }
    else if (q->front->priority > proc->exec_time) { 
  
        // Insert New Node before head 
        temp->next = q->front; 
        q->front = temp; 
    } 
    else { 
        struct priorityQnode* start = q->front;
        // Traverse the list and find a 
        // position to insert new node 
        while (start->next != NULL && 
               start->next->priority < proc->exec_time) { 
            start = start->next; 
        } 
  
        // Either at the ends of the list 
        // or at required position 
        temp->next = start->next; 
        start->next = temp; 
    }
}

// Function to remove a key from given priorityQ q
struct process* pop(struct priorityQ* q) {
    // If priorityQ is empty, return NULL.
    if (q->front == NULL)
        return NULL;

    // Store previous front and move front one node ahead
    struct priorityQnode* temp = q->front;

    q->front = q->front->next;

    // If front becomes NULL, then change rear also as NULL
    struct process* ret = temp->proc;
    free(temp);
    return ret;
}

int isEmpty(struct priorityQ* q) {
    return (q->front == NULL);
}

