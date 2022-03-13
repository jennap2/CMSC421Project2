#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "schedulers.h"

// add a task to the list
void add(char *name, int priority, int burst){
	struct node *temp;
	struct task *tempTask = malloc(sizeof(struct task));
	tempTask->name = name;
	tempTask->priority = priority;
	tempTask->burst = burst;
	printf(tempTask->name);
	insert(&temp, tempTask);
	traverse(temp);
}

// invoke the priority scheduler
void schedule(){
}

