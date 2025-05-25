#ifndef LIST_H  // If LIST_H is not defined...
#define LIST_H
/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

struct node {
    Task *task;
    struct node *next;
};

// insert and delete operations.
void insert(struct node **head, Task *task);
void delete(struct node **head, Task *task);
void traverse(struct node *head);
void insert_tail(struct node **head, Task *newTask);
Task* remove_head(struct node **head);

#endif
