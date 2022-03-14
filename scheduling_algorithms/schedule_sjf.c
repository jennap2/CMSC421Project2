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

// invoke the sjf scheduler
void schedule(){
	traverse(temp);
	printf("The Shortest-Job-First scheduling algorithm schedules tasks in order of the length of the tasks' next CPU burst\n");
}
