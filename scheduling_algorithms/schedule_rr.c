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
	traverse(tempNode);
	printf("The Round-Robin scheduling algorithm schedules tasks where each task in run for a time quantum (or for the remainder of its CPU burst)\n");
	pickNextTask();
}

// Run round robin
void pickNextTask(){
	reverseList();
	struct node *tempHead = tempNode;
	int quantum = 10;
	int sliceArray[]
	while(tempHead != NULL){
		// Run
		run(tempHead->task,tempHead->task->burst);
        	// Remove
		printf("Remove %s\n", tempHead->task->name);
        	delete(&tempNode,tempHead->task);
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
	printf("List reversed:\n");
	traverse(tempNode);
}
