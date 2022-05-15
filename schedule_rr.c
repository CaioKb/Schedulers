#include "schedule_rr.h"

#include <stdio.h>
#include <stdlib.h>

#include "CPU.h"

Node* head = NULL; //inicio da fila principal (ready list)
Node* priorityHead = NULL; // fila temporária

int hasPriority = 0;

void add(char* name, int priority, int burst){
   Task* task = malloc(sizeof(Task));

   task->name = name;
   task->priority = priority;
   task->burst = burst;

   insert(&head, task);
}

void schedule(){
   Task* nextTask;

   while (head != NULL) {
      nextTask = selectNextTask();

      CreatePriorityList(nextTask);

      while(priorityHead != NULL) {
         roundRobinScheduler(&priorityHead, priorityHead->task);
      }
   }
}

void roundRobinScheduler(Node** queue, Task* task)
{
   if (task->burst > QUANTUM) {
      run(task, QUANTUM);

      task->burst -= QUANTUM;

      insert_end(queue, task);
      delete(queue, task);

   }
   else {
      runFullTask(queue, task);
   }
}

void runFullTask(Node** queue, Task* task)
{
   run(task, task->burst);
   delete(queue, task);
   printf("Task %s has ended.\n", task->name);
}

Task* selectNextTask() {
   Task* nextTask = head->task; //primeira task da fila
   Node* aux = head->next; //recebe o segundo nó da fila

   while (aux != NULL) { //enquanto existir uma próxima task na fila
      int currentPriority = aux->task->priority;

      if(currentPriority < nextTask->priority) {
         nextTask = aux->task;
      }

      aux = aux->next;
   }

   return nextTask;
}

void CreatePriorityList(Task* task)
{
   insert(&priorityHead, task);
   delete(&head, task);

   Node* aux = head;

   while (aux != NULL) {
      if (aux->task->priority == task->priority) {
         insert(&priorityHead, aux->task);
         delete(&head, aux->task);
      }

      aux = aux->next;
   }
}