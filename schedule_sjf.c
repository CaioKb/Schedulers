#include "schedule_sjf.h"

#include <stdio.h>
#include <stdlib.h>

#include "CPU.h"

Node* head = NULL; //inicio da fila principal (ready list)
Node* priorityList = NULL;

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
    Task* nextTask = malloc(sizeof(Task));

    while (head != NULL) {
        nextTask = selectNextTask();
        createPriorityList(nextTask);

        while (priorityList != NULL) {
            runFullTask(&priorityList, priorityList->task);
        }
    }
}

void runFullTask(Node** queue, Task* task)
{
   run(task, task->burst);
   delete(queue, task);
   printf("Task %s has ended.\n", task->name);
}

Task* selectNextTask() 
{
   Task* nextTask = head->task; //primeira task da fila
   Node* aux = head->next; //recebe o segundo nó da fila

   while (aux != NULL) { //enquanto existir uma próxima task na fila
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
   insert(&priorityList, task);
   delete(&head, task);

   Node* aux = head;

   while (aux != NULL) {
      if (aux->task->burst == task->burst) {
         insert_end(&priorityList, aux->task);
         delete(&head, aux->task);
      }

      aux = aux->next;
   }
}