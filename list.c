/**
 * Various list operations
 */
 
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "list.h"
#include "task.h"

// add a new task to the list of tasks - adiciona no início
void insert(Node** head, Task* newTask) {
    // add the new task to the list 
    Node* newNode = malloc(sizeof(Node)); // cria um novo nó

    newNode->task = newTask; //atribui a tarefa ao novo vó
    newNode->next = *head;  //passa o atual primeiro nó da lista para a próxima posição
    *head = newNode; //início da lista agora aponta para o novo nó
}

void insert_end(Node** head, Task* task) {
    Node* newNode = malloc(sizeof(Node));
    Node* aux = *head;

    newNode->task = task;
    newNode->next = NULL;

    if (head != NULL) {

        while (aux->next != NULL) {
            aux = aux->next;
        }

        aux->next = newNode;
    }
    else {
        *head = newNode;
    }
}

// delete the selected task from the list
void delete(Node** head, Task *task) {
    Node* temp = malloc(sizeof(Node));
    Node* prev = malloc(sizeof(Node));

    temp = *head;
    // special case - beginning of list
    if (strcmp(task->name,temp->task->name) == 0) {
        *head = (*head)->next;
    }
    else {
        // interior or last element in the list
        prev = *head;
        temp = temp->next;
        while (strcmp(task->name,temp->task->name) != 0) {
            prev = temp;
            temp = temp->next;
        }

        prev->next = temp->next;
    }
}

// traverse the list
void traverse(Node *head) {
    Node* temp = malloc(sizeof(Node));
    temp = head;

    while (temp != NULL) {
        printf("[%s] [%d] [%d]\n",temp->task->name, temp->task->priority, temp->task->burst);
        temp = temp->next;
    }
}
