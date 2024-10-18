#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void user_func()
{
	pid_t pid;

	printf("User_func activated , creating a child process now \n");
	
	pid = fork();
	

	if(pid< 0)
	{
		printf("\n");
		printf("Child Creation Failed, Fork call interrupted \n");
		exit(EXIT_FAILURE);
	}

	else if(pid == 0)
	{	
		printf("\n---------------------------------\n");
		printf("child Process created\n");
		printf("PID of Child Process %d \n" ,getpid());
		printf("PPID of Child Process %d \n" , getppid());
		printf("\n");
		exit(0);	//exiting the child process
	}

	else
        {
                printf("\n---------------------------------\n");
                printf("Parent Process\n");
                printf("PID of Parent Process %d \n" ,getpid());
                printf("PPID of Parent Process %d \n" , getppid());
        }
//exit(0); //exiting the parent process
}

int main()
{
	signal(SIGINT , user_func);


	while(1)
	{
		printf("Program running , Waiting for SIGNIT(Ctrl+C)... \n");
		sleep(10);
	}



return 0;
}

