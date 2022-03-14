#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "schedulers.h"

/*GLOBAL VARIABLE*/
struct node *tempNode;

void pickNextTask();
void recursiveBackwards(struct node*);

// add a task to the list
void add(char *name, int priority, int burst){
        struct task *tempTask = malloc(sizeof(struct task));
        tempTask->name = name;
        tempTask->priority = priority;
        tempTask->burst = burst;
        insert(&tempNode, tempTask);
        printf("Inserted: %s \n", tempTask->name);
}

// invoke the fcfs scheduler
void schedule(){
	traverse(tempNode);
	printf("The First-Come, First-Served scheduling algorithm schedules tasks in the order in which they request the CPU\n");
	pickNextTask();
}

// Run and remove from the list in order of first to last request
void pickNextTask(){
	struct node *tempHead = tempNode;
	recursiveBackwards(tempHead);
}

// Recursively goes through out linked list backwards 
void recursiveBackwards(struct node* headPoint){
        if(headPoint == NULL){
                return;
        }
	recursiveBackwards(headPoint->next);
        run(headPoint->task,headPoint->task->burst);
        printf("Remove %s\n", headPoint->task->name);
        delete(&tempNode,headPoint->task);
}
