#ifndef SCHEDULE_RR_H
#define SCHEDULE_RR_H

#include "task.h" // Defines the Task structure
#include "list.h"   // Uses the list structure for the ready queue

// Global ready queue for RR tasks
// It's often better to pass the list to functions,
// but the project hints at global list for simplicity [cite: 1]
extern struct node *rr_ready_queue;

// Add a task to the RR ready queue
void rr_add(char *name, int priority, int burst);

// Invoke the RR scheduler
void rr_schedule();

#endif