#include "schedule_rr_fifo.h"

#include <stdio.h>
#include <stdlib.h>

#include "CPU.h"

Node* head = NULL;
Node* priorityQueues[MAX_PRIORITY];

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
    if (head == NULL) {
        printf("erro");
        return;
    }

    Node* aux = head;
    while (aux != NULL) {
        Task* task = aux->task;
        int taskPriority = task->priority;    

        if(taskPriority > 0 && taskPriority <= 10) {
            insert_end(&priorityQueues[taskPriority], task);
        }         

        aux = aux->next;      
    
    }
    for (int i = MIN_PRIORITY; i <= MAX_PRIORITY; i++) {
        Node* actualList = priorityQueues[i];

        while(actualList != NULL) {
            Task* nextTask = actualList->task;
            roundRobinScheduler(actualList, nextTask);
        }
    }
}

void roundRobinScheduler(Node* queue, Task* task)
{
   if (task->burst > QUANTUM) {
      run(task, QUANTUM);
      task->burst -= QUANTUM;

      insert_end(&queue, task);
      delete(&queue, task);

   }
   else {
      runFullTask(queue, task);
   }
}

void runFullTask(Node* queue, Task* task)
{
   run(task, task->burst);
   delete(&queue, task);
   printf("Task %s has ended.\n", task->name);
}

Task* selectHighestPriorityTask() {
   Task* nextTask = head->task;
   Node* aux = head->next;

   while (aux != NULL) {
      int currentPriority = aux->task->priority;

      if(currentPriority < nextTask->priority) {
         nextTask = aux->task;
      }

      aux = aux->next;
   }

   return nextTask;
}

Node* createPriorityList(Task* task)
{
    Node* newQueue = malloc(sizeof(Node));

    insert(&newQueue, task);
    delete(&head, task);


    Node* aux = head;

    while (aux != NULL) {

        if (aux->task->priority == task->priority) {
            insert_end(&newQueue, aux->task);
            delete(&head, aux->task);
        }

        aux = aux->next;
    }

    return newQueue;
}