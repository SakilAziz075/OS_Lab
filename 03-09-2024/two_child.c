#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <wait.h>

int main()
{
	pid_t p ,q;

	p = fork();
        
	if(p==0)
        {
                printf("This is a Child-process \n");
                printf("The Pid of the process is %d \n" , getpid());
                printf("The ParentPid of the process is %d \n" , getppid());
                printf("-----------------------------------\n");
        }

        else if(p>0)
        {	
        //        wait(NULL);
                printf("This is a Parent-process \n");
                printf("The Pid of the process is %d \n" , getpid());
                printf("-----------------------------------\n");
		
		q= fork();
        
	        if(q==0)
        	{ 	
        	        printf("This is the 2nd Child-process \n");
                	printf("The Pid of the process is %d \n" , getpid());
                	printf("The ParentPid of the process is %d \n" , getppid());
                	printf("-----------------------------------\n");
        	}	
		
		else if(q>0)
		{
	//		wait(NULL);
		}
	}


	else 
	{
		perror("fork() failure\n");
		return 1;
	}
	return 0;
}
