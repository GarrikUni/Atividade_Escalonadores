// schedule_rr.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h> // For strdup if you use it in rr_add
#include "schedule_rr.h"
#include "CPU.h" // For QUANTUM and run() [cite: 3]

// Define the global ready queue
struct node *rr_ready_queue = NULL;

// Timer-related global (as per project description [cite: 1])
// volatile int time_slice_expired = 0; // This will be set by your timer thread later

void rr_add(char *name, int priority, int burst) {
    Task *newTask = (Task *)malloc(sizeof(Task));
    if (!newTask) {
        fprintf(stderr, "Error allocating memory for task\n");
        return;
    }
    // strdup allocates memory, ensure it's freed when task is done
    newTask->name = strdup(name);
    newTask->priority = priority; // Priority not used in basic RR, but part of Task struct
    newTask->burst = burst;
    // Add any other fields from task.h if necessary

    // Use your new list function to add to the tail for FIFO
    insert_tail(&rr_ready_queue, newTask);
    printf("RR: Added task %s, Priority: %d, Burst: %d\n", name, priority, burst);
}

void rr_schedule() {
    Task *current_task;
    int time_slice = QUANTUM; // QUANTUM is defined in CPU.h [cite: 3]

    printf("Starting RR Scheduler...\n");

    // Main scheduling loop: continues as long as there are tasks in the ready queue
    // You'll need an is_empty function for your list or check rr_ready_queue != NULL
    while (rr_ready_queue != NULL /* or !is_empty(rr_ready_queue) */) {
        // Dequeue task from the head of the ready queue
        current_task = remove_head(&rr_ready_queue); // Assuming you implement remove_head

        if (current_task == NULL) { // Should not happen if while condition is correct
            break;
        }

        printf("RR: Running task [%s] (Burst: %d)\n", current_task->name, current_task->burst);

        int run_time = (current_task->burst < time_slice) ? current_task->burst : time_slice;

        // Use the provided run function from CPU.c
        run(current_task, run_time); // [cite: 3]

        current_task->burst -= run_time;

        if (current_task->burst > 0) {
            // Task not finished, add it back to the tail of the ready queue
            printf("RR: Task %s not finished, re-adding to queue (Remaining Burst: %d).\n", current_task->name, current_task->burst);
            insert_tail(&rr_ready_queue, current_task);
        } else {
            // Task finished
            printf("RR: Task %s finished.\n", current_task->name);
            free(current_task->name); // Free the duplicated string
            free(current_task);       // Free the task structure itself
        }

        // Here, you would normally wait for the timer interrupt/flag.
        // For now, the loop just continues. The timer thread [cite: 1] will be a later addition.
        // time_slice_expired = 0; // Reset flag after handling
    }
    printf("RR Scheduler finished: No more tasks in the queue.\n");
}