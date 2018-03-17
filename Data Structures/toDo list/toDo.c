/**
* CS 261 Assignment 4
* Name: Jonathan Perry
* Date: 08/07/2017
*/

#include "dynamicArray.h"
#include "task.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/**
* Loads into heap a list from a file with lines formatted like
* "priority, name".
* @param heap
* @param file
*/
void listLoad(DynamicArray* heap, FILE* file)
{
	const int FORMAT_LENGTH = 256;
	char format[FORMAT_LENGTH];
	snprintf(format, FORMAT_LENGTH, "%%d, %%%d[^\n]", TASK_NAME_SIZE);

	Task temp;
	while (fscanf(file, format, &temp.priority, &temp.name) == 2)
	{
		dyHeapAdd(heap, taskNew(temp.priority, temp.name), taskCompare);
	}
}

/**
* Writes to a file all tasks in heap with lines formatted like
* "priority, name".
* @param heap
* @param file
*/
void listSave(DynamicArray* heap, FILE* file)
{
	for (int i = 0; i < dySize(heap); i++)
	{
		Task* task = dyGet(heap, i);
		fprintf(file, "%d, %s\n", task->priority, task->name);
	}
}

/**
* Prints every task in heap.
* @param heap
*/
void listPrint(DynamicArray* heap)
{
	DynamicArray* temp = dyNew(dySize(heap));
	dyCopy(heap, temp);
	while (dySize(temp) > 0)
	{
		Task* task = dyHeapGetMin(temp);
		printf("\n");
		taskPrint(task);
		printf("\n");
		dyHeapRemoveMin(temp, taskCompare);
	}
	printf("\n");
	dyDelete(temp);
}

/**
* Handles the given command.
* @param list
* @param command
*/
void handleCommand(DynamicArray* list, char command)
{
	char *myFile = malloc(sizeof(char) * 128); // Allocate memory for 128 characters 
	char *description = malloc(sizeof(char) * 256); // Allocate memory for 256 characters
	int priority;
	// FIXME: Implement
	switch (command) 
	{
	case 'a': // add a new task
		printf("Please enter the task description: ");
		fgets(description, 100, stdin);
		if (description[strlen(description) - 1] == '\n') 
			description[strlen(description) - 1] = 0;

		printf("Please enter the task priority (0-999): ");
		scanf("%d", &priority);
		while (getchar() != '\n');

		Task *myTask = taskNew(priority, description); // Create the new task
		dyHeapAdd(list, myTask, taskCompare); // Add the new task into the heap
		printf("The task '%s' has been added to the list.\n\n", description);
		break;
	case 'e': // exit
		printf("Bye!\n");
		break;
	case 'g': // get the first task
		if (dySize(list) != 0) // is the list not empty?
			printf("Your first task is: %s\n\n", ((struct Task *)dyHeapGetMin(list))->name);
		else // the list is empty
			printf("Your to-do list is empty!\n\n");
		break;
	case 'l': // load a to-do list from a file
		printf("Please enter the myFile: ");
		fgets(myFile, 100, stdin);
		if (myFile[strlen(myFile) - 1] == '\n') 
			myFile[strlen(myFile) - 1] = 0;
		FILE *myReader = fopen(myFile, "r");
		listLoad(list, myReader);
		printf("The list has been loaded successfully from the file.\n\n");
		fclose(myReader);
		break;
	case 'p': // print the list
		if (dySize(list) == 0) // is the list empty?
			printf("Your to-do list is empty!\n");
		else 
			listPrint(list);
		break;
	case 'r':
		if (dySize(list) == 0) // is the list empty?
			printf("Your to-do list is empty!\n\n");
		else
		{
			Task* removeTask = (struct Task *)dyHeapGetMin(list);
			printf("Your first task '%s' has been removed from the list.\n\n", removeTask->name);
			dyHeapRemoveMin(list, taskCompare);
			taskDelete(removeTask);
		}
		break;
	case 's':
		printf("Please enter the myFile: ");
		fgets(myFile, 100, stdin);
		if (myFile[strlen(myFile) - 1] == '\n') 
			myFile[strlen(myFile) - 1] = 0;
		FILE *myWriter = fopen(myFile, "w+");
		listSave(list, myWriter);
		printf("The list was saved to the file: '%s'.\n\n", myFile);
		fclose(myWriter);
		break;
	}
	free(description);
	free(myFile);
}

int main()
{
	// Implement
	printf("\n\n** TO-DO LIST APPLICATION **\n\n");
	DynamicArray* list = dyNew(8);
	char command = ' ';
	do
	{
		printf("Press:\n"
			"'l' to load to-do list from a file\n"
			"'s' to save to-do list to a file\n"
			"'a' to add a new task\n"
			"'g' to get the first task\n"
			"'r' to remove the first task\n"
			"'p' to print the list\n"
			"'e' to exit the program\n"
		);
		command = getchar();
		// Eat newlines
		while (getchar() != '\n');
		handleCommand(list, command);
	} while (command != 'e');
	for (int i = 0; i < dySize(list); i++) {
		Task *t = dyGet(list, i);
		taskDelete(t);
	}
	dyDelete(list);
	return 0;
}
