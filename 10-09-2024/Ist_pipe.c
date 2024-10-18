#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
	int fd[2] , n;

	char buffer[100];
	pid_t p;
	pipe(fd);
	p = fork();

	if(p>0)
	{
		printf("Parent Passing Value to child\n");
		write(fd[1] , "Hello\n",6);
	}

	else
	{
		printf("child receiving data from Parent \n");
		n = read(fd[0], buffer , 100);
		write(1, buffer,n);
	}
	
return 0;
}
