#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<fcntl.h>
#include<unistd.h>

int main(int argc, char *argv[])
{
	struct flock fl = {F_UNLCK, SEEK_SET, 0, 100, 0};
	int fd;
       	int fsize, offset;
	char buff[50];

	//open the file that is passed as a command line argument to the program in read and write mode
	if((fd = open(argv[1], O_RDWR)) == -1)
	{
		perror("Error Opening File\n");
		exit(1);
	}

	printf("File not locked by any process\n");
	printf("Press Enter to lock the file\n");
	getchar();  //gets a key hit from the user

	fl.l_type = F_WRLCK;  // replace the F_UNLCK to WRLCK for the structure variable fl
	fl.l_pid = getpid();  // replace the pid from 0 to the current process id for the structure variable fl

	if(fcntl(fd,F_SETLK, &fl) == -1)
	{
		perror("Cannot set exclusive lock\n");
		exit(1);
	}

	else if(fl.l_type!=F_UNLCK)
	{
		printf("File has been exclusively locked by process : %d\n", fl.l_pid);
	}
	else
	{
		printf("File is not Locked \n");
	}


	printf("Press Enter to release lock \n");
	getchar();

	fl.l_type = F_UNLCK; // replace the F_WRLCK to F_UNLCK to unlock the file
	printf("File has been unlocked\n");

	//finding the offset value of the last 50 bytes of data
	fsize = lseek(fd,0,SEEK_END);
	offset = fsize - 50;

	//setting the cursor to the offset found
	lseek(fd, offset, SEEK_SET);

	//reading the last 50 bytes of data and print it
	read(fd, buff, 50);
	printf("Last 50 bytes of the file is \n");
	printf("\n");
	printf("%s\n", buff);

	return 0;
}
