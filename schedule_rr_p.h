#ifndef SCHEDULE_RR_P_H
#define SCHEDULE_RR_P_H

#include "task.h"
#include "list.h"

// Define the number of priority levels.
// The project states highest priority is 1.
// Let's assume a maximum based on common practice or other hints (e.g., MAX_PRIORITY in schedule_edf.h was 10).
// If your priorities are 1-indexed, you'll need to adjust array access (e.g., priority 1 maps to index 0).
#define MAX_PRIORITY_LEVELS 10 // Example: for priorities 1 through 10

// Array of ready queues, one for each priority level.
// 'extern' means it's defined in a .c file (schedule_rr_p.c).
extern struct node *priority_queues[MAX_PRIORITY_LEVELS];

void* timer_function(void* arg);

void rr_p_add(char *name, int priority, int burst);

void rr_p_schedule();

#endif // SCHEDULE_RR_P_H