/**
 * Driver.c
 *
 * Schedule is in the format
 *
 *  [name] [priority] [CPU burst]
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "task.h"
#include "list.h"
// #include "schedule_edf.h"
// #include "schedule_rr.h" 
#include "schedule_rr_p.h"

#define SIZE    100

int main(int argc, char *argv[])
{
    FILE *in;
    char *temp;
    char task[SIZE];

    char *name;
    int priority;
    int burst;
    // int deadline;

    in = fopen(argv[1],"r");
    
    while (fgets(task,SIZE,in) != NULL) {
        temp = strdup(task);
        name = strsep(&temp,",");
        priority = atoi(strsep(&temp,","));
        burst = atoi(strsep(&temp,","));
        //Only to EDF algorithm
        // deadline = atoi(srtsep(&temp, ","));

        // add the task to the scheduler's list of tasks
        // add(name,priority,burst, deadline); //to EDF only

        // rr_add(name, priority, burst); // <- Round-Robin add task
        rr_p_add(name,priority,burst); // <- RR_Priority

        free(temp);
    }

    fclose(in);

    // invoke the scheduler
    // schedule();
    // rr_schedule();
    rr_p_schedule();

    return 0;
}
