/*
* CS 261 Assignment 4
* Name: Jonathan Perry
* Date: 08/07/2017
*/

#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
* Creates a new task with the given priority and name.
* @param priority
* @param name
* @return  The new task.
*/
Task* taskNew(int priority, char* name)
{
	Task *myTask = malloc(sizeof(Task)); // allocate space for the new task
	strcpy(myTask->name, name); // store the name received 
	myTask->priority = priority; // store the priority variable received
	return myTask; // Return the newly created task
}

/**
* Frees a dynamically allocated task.
* @param task
*/
void taskDelete(Task* task)
{
	free(task);
}

/**
* Casts left and right to Task pointers and returns
* -1 if left's priority < right's priority,
*  1 if left's priority > right's priority,
*  0 if left's priority == right's priority.
* @param left  Task pointer.
* @param right  Task pointer.
* @return
*/
int taskCompare(void* left, void* right)
{
	Task* leftTask = (Task*)left; 
	Task* rightTask = (Task*)right;

	if (leftTask->priority < rightTask->priority)
		return -1;
	else if (leftTask->priority > rightTask->priority)
		return 1;
	else
		return 0;
}

/**
* Prints a task as a (priority, name) pair.
* @param value  Task pointer.
*/
void taskPrint(void* value)
{
	Task* task = (Task*)value;
	printf("(%d, %s)", task->priority, task->name);
}