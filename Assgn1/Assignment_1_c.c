#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
	pid_t pid;
	int status;

	// First fork to create child

	pid = fork();

	if (pid < 0) 
	{
		// Error in creating child process
		printf("Fork failed!\n");
		exit(1);
	}

	if (pid == 0) 
	{
		// Child process
		char *args[] = {"./child_program", NULL};  // Replace ./child_program with your actual program path
		printf("Child Process: Executing execv() to replace with another program\n");
		execv(args[0], args);  // Overlay new program into child
				       // If execv fails
		printf("execv failed!\n");
		exit(1);
	}
	else
	{
		// Parent process
		wait(&status);  // Wait for child to finish
		if (WIFEXITED(status))
		{
			printf("Parent Process: Child exited with status = %d\n", WEXITSTATUS(status));
		} 

		else 
		{
			printf("Parent Process: Child process did not terminate normally.\n");
		}
	}

	return 0;
}

