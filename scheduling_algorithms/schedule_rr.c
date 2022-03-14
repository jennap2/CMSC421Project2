#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "schedulers.h"

/*GLOBAL VARIABLE*/
struct node *tempNode;

void pickNextTask();
void reverseList();

// add a task to the list
void add(char *name, int priority, int burst){
        struct task *tempTask = malloc(sizeof(struct task));
        tempTask->name = name;
        tempTask->priority = priority;
        tempTask->burst = burst;
        insert(&tempNode, tempTask);
        printf("Inserted: %s \n", tempTask->name);
}

// invoke the rr scheduler
void schedule(){
	printf("\nTraverse the linked list:\n");
	traverse(tempNode);
	printf("\nThe Round-Robin scheduling algorithm schedules tasks where each task in run for a time quantum (or for the remainder of its CPU burst)\n");
	pickNextTask();
}

// Run round robin
void pickNextTask(){
	reverseList();
	int quantum = 10;
	int slice = 0;
	// Loop through linked list until everything deleted
	while(tempNode != NULL){
		// Temp linked list to loop through 
		struct node *loopHead = tempNode;
		while(loopHead != NULL){
			// Check if burst remaining is greater or less than time quantum
			if(loopHead->task->burst < quantum){
				// Run for remainder of burst
				run(loopHead->task, loopHead->task->burst);
				loopHead->task->burst -= loopHead->task->burst;
				// Remove
                		printf("Task completed: remove %s\n", loopHead->task->name);
                		delete(&tempNode,loopHead->task);
			}
			else{
				slice = loopHead->task->burst - quantum;
				// Run
				run(loopHead->task,quantum);
				loopHead->task->burst = slice;
			}
			loopHead = loopHead->next;
		}
	}
}

// Recursively goes through linked list backwards
void reverseList(){
        struct node *currNode = tempNode;
	struct node *prevNode = NULL, *nextNode = NULL;
	while(currNode != NULL){
		nextNode = currNode->next;
		currNode->next = prevNode;
		prevNode = currNode;
		currNode = nextNode;
	}
	tempNode = prevNode;
	printf("\nList reversed:\n");
	traverse(tempNode);
	printf("\n");
}
