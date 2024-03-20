#include <stdio.h>
#include <stdlib.h>

void red () {
	printf("\033[1;31m");
}

void gold() {
	printf("\033[0;33m");
}

void green() {
	printf("\033[0;32m");
}

void reset () {
	printf("\033[0m");
}

typedef struct {
	int id;
	char name[50];
	char description[100];
	char dueDate[25];
	int priority;
	int isFinished;
} Task;

Task tasks[25];
int numberOfTasks = 0;

void addTask() {
	if (numberOfTasks >= 25) {
        red();
        printf("## YOU CAN'T ADD MORE TASKS, TASK LIMIT COUNT REACHED.");
        reset();
        printf("\n\n---------------------------------------------------\n\n");
        return;
    }
    
    Task newTask;
    
    printf("-- Enter Task Name: ");
    scanf(" %[^\n]", newTask.name);

    printf("-- Enter Task Description: ");
    scanf(" %[^\n]", newTask.description);

    printf("-- Enter Due Date (DD/MM/YYYY): ");
    scanf("%s", newTask.dueDate);

    printf("-- Enter Priority (1: Low, 2: Medium, 3: High): ");
    scanf("%d", &newTask.priority);

    newTask.isFinished = 0;

    newTask.id = numberOfTasks + 1;
    tasks[numberOfTasks++] = newTask;

    printf("\n---------------------------------------------------\n");
    green();
    printf("# TASK ADDED SUCCESSFULLY.\n");
    reset();
    printf("---------------------------------------------------\n\n");
	
}

void editTask () {
	int i, taskId, isFound = 0;
	
    printf("-- Enter The Task ID: ");
    scanf("%d", &taskId);

    for (i = 0; i < numberOfTasks; i++) {
        if (tasks[i].id == taskId) {
            printf("-- Enter New Task Name: ");
            scanf(" %[^\n]", tasks[i].name);

            printf("-- Enter New Task Description: ");
            scanf(" %[^\n]", tasks[i].description);

            printf("-- Enter New Due Date (DD/MM/YYYY): ");
            scanf("%s", tasks[i].dueDate);

            printf("-- Enter New Priority (1: Low, 2: Medium, 3: High): ");
            scanf("%d", &tasks[i].priority);

			printf("\n---------------------------------------------------\n");
			green();
        	printf("# TASK MODIFIED SUCCESSFULLY.\n");
        	reset();
        	printf("---------------------------------------------------\n\n");
            isFound = 1;
            break;
        }
    }

    if (!isFound) {
    	printf("\n---------------------------------------------------\n");
    	red();
        printf("# TASK WITH ID %d NOT FOUND.\n", taskId);
        reset();
        printf("---------------------------------------------------\n\n");
    }
}

void deleteTask() {
	int i, taskId;
	
    printf("-- Enter the ID of the Task you want to Delete: ");
    scanf("%d", &taskId);

    int isFound = 0;
    Task *taskToDelete = NULL;

    for (i = 0; i < numberOfTasks; i++) {
        if (tasks[i].id == taskId) {
            taskToDelete = &tasks[i];
            isFound = 1;
            break;
        }
    }

    if (isFound) { 
        for (i = taskToDelete; i < numberOfTasks - 1; i++) {
            tasks[i] = tasks[i + 1];
        }
        numberOfTasks--;
        
        printf("\n---------------------------------------------------\n");
        green();
        printf("# TASK WITH ID %d DELETED SUCCESSFULLY.\n", taskId);
        reset();
        printf("---------------------------------------------------\n\n");
    } 
	
	else {
		printf("\n---------------------------------------------------\n");
        red();
        printf("# TASK WITH ID %d NOT FOUND.\n", taskId);
        reset();
        printf("---------------------------------------------------\n\n");
    }
}

void printTask(Task task) {
	gold();
    printf(" (ID: %d)", task.id);
    reset();
    printf("\nTask Name: %s", task.name);
    printf("\nTask Description: %s", task.description);
    printf("\nDue Date: %s", task.dueDate);
    printf("\nPriority: %d", task.priority);
    printf("\nCompleted: %s", task.isFinished ? "Yes" : "No");
}

void listTasks() {
	int i, j;
	
    if (numberOfTasks == 0) {
    	red();
        printf("# NO TASKS TO DISPLAY.");
        reset();
        printf("\n\n---------------------------------------------------\n\n");
        return;
    }

    for (i = 0; i < numberOfTasks - 1; i++) {
        for (j = 0; j < numberOfTasks - i - 1; j++) {
            if (tasks[j].priority < tasks[j + 1].priority) {
                Task temp = tasks[j];
                tasks[j] = tasks[j + 1];
                tasks[j + 1] = temp;
            }
        }
    }

    for (i = 0; i < numberOfTasks; i++) {
    	gold();
    	printf("# TASK NUMBER %d", (i + 1));
    	reset();
    	printTask(tasks[i]);
		printf("\n\n");
    }
}

void markTaskAsCompleted() {
	int i, taskId, isFound = 0;
	
    printf("-- Enter the ID of the Task to Mark as Complete: ");
    scanf("%d", &taskId);

    for (i = 0; i < numberOfTasks; i++) {
        if (tasks[i].id == taskId) {
            tasks[i].isFinished = 1;
            printf("\n---------------------------------------------------\n");
	        green();
	        printf("# TASK WITH ID %d MARKED AS COMPLETE.\n", taskId);
	        reset();
	        printf("---------------------------------------------------\n\n");
            isFound = 1;
            break;
        }
    }

    if (!isFound) {
    	printf("\n---------------------------------------------------\n");
        red();
        printf("# TASK WITH ID %d NOT FOUND.\n", taskId);
        reset();
        printf("---------------------------------------------------\n\n");
    }
}

int main() {
    int userChoice, taskId;
    
    printf("#################### To Do App ####################\n\n");
    printf("Welcome to the To Do App, where you can add, edit,\n");
    printf("delete, list, and mark as complete tasks.\n\n");
    
    do {
        printf("# To Do App Menu:\n\n");
        printf("1. Add Task\n");
        printf("2. Edit Task\n");
        printf("3. Delete Task\n");
        printf("4. List Tasks\n");
        printf("5. Mark Task as Completed\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        switch (userChoice) {
            case 1:
            	printf("\n---------------------------------------------------\n");
            	gold();
	        	printf("# ADD TASK.");
	        	reset();
	        	printf("\n---------------------------------------------------\n\n");
                addTask();
                break;
            case 2:
            	printf("\n---------------------------------------------------\n");
            	gold();
	        	printf("# EDIT TASK.");
	        	reset();
	        	printf("\n---------------------------------------------------\n\n");
	        	listTasks();
            	editTask();
            	break;
            case 3:
            	printf("\n---------------------------------------------------\n");
            	gold();
	        	printf("# DELETE TASK.");
	        	reset();
	        	printf("\n---------------------------------------------------\n\n");
	        	listTasks();
            	deleteTask();
            	break;
            case 4:
            	printf("\n---------------------------------------------------\n");
            	gold();
	        	printf("# LIST TASKS.");
	        	reset();
	        	printf("\n---------------------------------------------------\n\n");
				listTasks();
                break;
            case 5:
            	printf("\n---------------------------------------------------\n");
            	gold();
	        	printf("# MARK TASK AS COMPLETED.");
	        	reset();
	        	printf("\n---------------------------------------------------\n\n");
	        	listTasks();
                markTaskAsCompleted();
                break;
            case 6:
                printf("\n---------------------------------------------------\n");
            	gold();
                printf("# GOODBYE!");
                reset();
                printf("\n---------------------------------------------------\n\n");
                break;
            default:
            	printf("\n---------------------------------------------------\n");
            	red();
                printf("# INVALID CHOICE, PLEASE ENTER A VALID CHOICE.");
                reset();
                printf("\n---------------------------------------------------\n\n");
        }
    } while (userChoice != 6);

    return 0;
}
