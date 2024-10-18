#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() 
{
	pid_t pid, grandchild_pid;
	int child_count = 0, grandchild_count = 0;

	pid = fork();  // Creating the first child

	if (pid < 0) 
	{
		printf("Fork failed!\n");
		exit(1);  // Exit with failure status
	}

	if (pid == 0) 
	
	{  // Child process
		printf("Child process created. PID: %d, PPID: %d\n", getpid(), getppid());
		grandchild_pid = fork();  // Create grandchild

		if (grandchild_pid < 0) 
		{
			printf("Fork failed for grandchild!\n");
			exit(1);
		}

		else if (grandchild_pid == 0) 
		{
		      	// Grandchild process
			printf("Grandchild process created. PID: %d, PPID: %d\n", getpid(), getppid());
			printf("My roll number is: CSB22012\n");
			exit(0);
		} 
		
		else 
		{
		      	// Child waits for grandchild to finish
			wait(NULL);
			exit(0);
		}

	}
       	else 
	{      
		// Parent process
		child_count++;
		wait(NULL);  // Wait for child to finish

		// Since the grandchild is created by the child, we count the grandchild process here
		if (pid > 0) 
		{
			grandchild_count++;
		}

		printf("Parent process. PID: %d, PPID: %d\n", getpid(), getppid());
		printf("Number of child processes created: %d\n", child_count);
		printf("Number of grandchild processes created: %d\n", grandchild_count);

		exit(0);
	}
return 0;
}

