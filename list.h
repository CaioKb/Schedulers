/**
 * list data structure containing the tasks in the system
 */

#include "task.h"

typedef struct node {
    Task* task;
    struct node* next;
} Node;

// insert and delete operations.
void insert(Node** head, Task* task);

void insert_end(Node** head, Task* task);

void delete(Node** head, Task* task);

void traverse(Node* head);
