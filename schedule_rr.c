#include "schedule_rr.h"

#include <stdio.h>
#include <stdlib.h>

#include "CPU.h"

Node* head = NULL;
Node* priorityQueue = NULL;

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
      highestPriotiyTask = selectHighestPriorityTask();
      createPriorityList(highestPriotiyTask);

      while(priorityQueue != NULL) {
         Task* nextTask = priorityQueue->task;
         roundRobinScheduler(nextTask);
      }
   }
}

void roundRobinScheduler(Task* task)
{
   if (task->burst > QUANTUM) {
      run(task, QUANTUM);
      task->burst -= QUANTUM;

      insert_end(&priorityQueue, task);
      delete(&priorityQueue, task);

   }
   else {
      runFullTask(task);
   }
}

void runFullTask(Task* task)
{
   run(task, task->burst);
   delete(&priorityQueue, task);
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

void createPriorityList(Task* task)
{
   insert(&priorityQueue, task);
   delete(&head, task);

   Node* aux = head;

   while (aux != NULL) {
      if (aux->task->priority == task->priority) {
         insert_end(&priorityQueue, aux->task);
         delete(&head, aux->task);
      }

      aux = aux->next;
   }
}