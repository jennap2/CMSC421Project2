#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "list.h"
#include "schedulers.h"

//GLOBAL VARIABLE
struct node *tempNode;
struct node *priorityList;

void pickNextTask();
bool getPriority();
void roundRobin();

// add a task to the list
void add(char *name, int priority, int burst){
        struct task *tempTask = malloc(sizeof(struct task));
        tempTask->name = name;
        tempTask->priority = priority;
        tempTask->burst = burst;
        insert(&tempNode, tempTask);
        printf("Inserted: %s \n", tempTask->name);
}

// invoke the priority rr scheduler
void schedule(){
	printf("\nTraverse the linked list:\n");
	traverse(tempNode);
	printf("\nThe Priority RR Scheduling algorithm schedules tasks in order of priority and uses rr scheduling for tasks with equal priority\n");
	pickNextTask();
}

// Calls getPriority and roundRobin to know what to run and remove
void pickNextTask(){
	struct node* run_task = tempNode;
	bool result = false;
	while(tempNode != NULL){
		result = getPriority();
		// Check to see if there is tasks with equal priorities, if equal run roundRobin
		if(result){
			printf("\nEqual priorities found: run Round Robin algorithm\n");
			roundRobin();
		}
		else{
			// Run and remove
			run(priorityList->task,priorityList->task->burst);
        		printf("Task completed: remove %s\n", priorityList->task->name);
        		delete(&tempNode, priorityList->task);
			delete(&priorityList, priorityList->task);
		}
	}
}


// Gets the highest priority and checks if there are any other tasks with same priority
bool getPriority(){
	struct node* tempHead = tempNode;
        int priority = tempNode->task->priority;
	bool result = false;
	// Find the highest priority task
	while(tempHead != NULL){
                if(tempHead->task->priority >= priority){
			priority = tempHead->task->priority;
		}
                tempHead = tempHead->next;
        }
	tempHead = tempNode;
	// Find if there are any more tasks with same priority
	while(tempHead != NULL){
		// If equal priority tasks, add to the priorityList
		if(tempHead->task->priority == priority){
			insert(&priorityList, tempHead->task);
			if(priorityList->next != NULL){
				result = true;
			}
		}
		tempHead = tempHead->next;
	}
	return result;
}

// Round Robin scheduling algorithm for equal priorities
void roundRobin(){
	int quantum = 10;
        int slice = 0;
        // Loop through priority list until everything deleted
        while(priorityList != NULL){
                // Temp linked list to loop through
                struct node *loopHead = priorityList;
                while(loopHead != NULL){
                        // Check if burst remaining is greater or less than time quantum
                        if(loopHead->task->burst <= quantum){
                                // Run for remainder of burst
                                run(loopHead->task, loopHead->task->burst);
                                loopHead->task->burst -= loopHead->task->burst;
                                // Remove
                                printf("Task completed: remove %s\n", loopHead->task->name);
                                delete(&tempNode,loopHead->task);
				delete(&priorityList, loopHead->task);
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
