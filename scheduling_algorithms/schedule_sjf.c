#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "schedulers.h"

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

// invoke the sjf scheduler
void schedule(){
	printf("\nTraverse the linked list:\n");
        traverse(tempNode);
	printf("\nThe Shortest-Job-First scheduling algorithm schedules tasks in order of least to greatest length of the tasks CPU burst\n");
	pickNextTask();
}

// Run and remove from the list in order of highest to lowest burst
void pickNextTask(){
        struct node* tempHead = tempNode;
        struct node* run_task = tempNode;
        while(tempNode != NULL){
		// Loop through temp list
                int burstHead = tempNode->task->burst;
                while(tempHead != NULL){
			// Find highest burst
                        if(burstHead >= tempHead->task->burst){
                                burstHead = tempHead->task->burst;
                                run_task = tempHead;
                        }
                        tempHead = tempHead->next;
                }
		// Run and remove
                run(run_task->task,run_task->task->burst);
                printf("Next lowest burst ran: remove %s\n", run_task->task->name);
                delete(&tempNode,run_task->task);
                tempHead = tempNode;
        }
}
