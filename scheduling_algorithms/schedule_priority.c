#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "list.h"
#include "schedulers.h"
#include "cpu.h"

/*GLOBAL VARIABLE*/
struct node *tempNode;

void pickNextTask();

// add a task to the list
void add(char *name, int priority, int burst){
	struct task *tempTask = malloc(sizeof(struct task));
	tempTask->name = name;
	tempTask->priority = priority;
	tempTask->burst = burst;
	insert(&tempNode, tempTask);
	printf("Inserted: %s \n", tempTask->name);
}

// invoke the priority scheduler
void schedule(){
	printf("\nTraverse the linked list:\n");
        traverse(tempNode);
	printf("\nThe Priority scheduling algorithm schedules tasks based on priority(Highest to Lowest)\n");
	pickNextTask();
}

// Run and remove from the list in order of highest to lowest priority
void pickNextTask(){
	struct node* tempHead = tempNode;
	struct node* run_task = tempNode;
	while(tempNode != NULL){
        	int priorityHead = tempNode->task->priority;
		while(tempHead != NULL){
			if(priorityHead <= tempHead->task->priority){
				priorityHead = tempHead->task->priority;
				run_task = tempHead;
			}
			tempHead = tempHead->next;
        	}
		run(run_task->task,run_task->task->burst);
		printf("Next highest priority ran: remove %s\n", run_task->task->name);
		delete(&tempNode,run_task->task);
		tempHead = tempNode;
	}
}

