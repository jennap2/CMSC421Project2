#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "schedulers.h"

/*GLOBAL VARIABLE*/
struct node *temp;

void pickNextTask();

// add a task to the list
void add(char *name, int priority, int burst){
        struct task *tempTask = malloc(sizeof(struct task));
        tempTask->name = name;
        tempTask->priority = priority;
        tempTask->burst = burst;
        insert(&temp, tempTask);
        printf("Inserted: %s \n", tempTask->name);
}

// invoke the fcfs scheduler
void schedule(){
	traverse(temp);
	printf("The First-Come, First-Served scheduling algorithm schedules tasks in the order in which they request the CPU\n");
}
