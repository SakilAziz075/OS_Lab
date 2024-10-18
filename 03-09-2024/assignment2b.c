#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// Program to send a signal to a process using kill()

int main() 
{
	pid_t pid;
	int signal_id;

	// Enter Input: Process ID and Signal ID

	printf("Enter Process ID: ");
	scanf("%d", &pid);

	printf("Enter Signal ID: ");
	scanf("%d", &signal_id);

	// Sending the signal to the given process
	if (kill(pid, signal_id) == 0) 
	{
		printf("Signal %d sent to process %d successfully\n", signal_id, pid);
	} 

	else 
	{
		printf("Failed to send signal");
	}

	return 0;
}

