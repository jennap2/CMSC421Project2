#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "schedulers.h"

/*GLOBAL VARIABLE*/
struct node *temp;

void pickNextTask(Task *task, int slice);

// add a task to the list
void add(char *name, int priority, int burst){
        struct task *tempTask = malloc(sizeof(struct task));
        tempTask->name = name;
        tempTask->priority = priority;
        tempTask->burst = burst;
        insert(&temp, tempTask);
        printf("Inserted: %s \n", tempTask->name);
}

// invoke the rr scheduler
void schedule(){
	traverse(temp);
	printf("The Round-Robin scheduling algorithm schedules tasks where each task in run for a time quantum (or for the remainder of its CPU burst)\n");
}
