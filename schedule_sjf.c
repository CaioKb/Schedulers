#include "schedule_sjf.h"

#include <stdio.h>
#include <stdlib.h>

#include "CPU.h"

Node* head = NULL;
Node* runningList = NULL;

void add(char* name, int priority, int burst)
{
   Task* task = malloc(sizeof(Task));

   task->name = name;
   task->priority = priority;
   task->burst = burst;

   insert(&head, task);
}

void schedule()
{
    Task* highestPriotiyTask = malloc(sizeof(Task));

    while (head != NULL) {
        highestPriotiyTask = selectSmallestBurstTask();
        createPriorityList(highestPriotiyTask);

        while (runningList != NULL) {
            Task* nextTask = runningList->task;
            runShortestTasks(nextTask);
        }
    }
}

void runShortestTasks(Task* task)
{
   run(task, task->burst);
   delete(&runningList, task);
   printf("Task %s has ended.\n", task->name);
}

Task* selectSmallestBurstTask() 
{
   Task* nextTask = head->task;
   Node* aux = head->next;

   while (aux != NULL) {
      int currentBurst = aux->task->burst;

      if(currentBurst < nextTask->burst) {
         nextTask = aux->task;
      }

      aux = aux->next;
   }

   return nextTask;
}

void createPriorityList (Task* task)
{
    insert(&runningList, task);
    delete(&head, task);

    Node* aux = head;

    while (aux != NULL) {
        if (aux->task->burst == task->burst) {
            insert_end(&runningList, aux->task);
            delete(&head, aux->task);
        }

        aux = aux->next;
   }
}