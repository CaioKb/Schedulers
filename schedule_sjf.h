#define MIN_PRIORITY 1
#define MAX_PRIORITY 10

#include "list.h"
#include "task.h"

// add a task to the list 
void add(char *name, int priority, int burst);

// invoke the scheduler
void schedule();
void runShortestTasks(Task* task);

Task* selectSmallestBurstTask();
void createPriorityList(Task* task);