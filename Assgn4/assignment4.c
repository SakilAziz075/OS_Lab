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
    if((fd = open(argv[1], O_RDWR)) == -1)
    {
        printf("Error Opening File\n");
        exit(0);
    }
    printf("File not locked by any process\n");
    printf("Press Enter to lock the file\n");
    getchar();  
    fl.l_type = F_WRLCK; 
    fl.l_pid = getpid();  
    if(fcntl(fd,F_SETLK, &fl) == -1)
    {
        printf("Cannot set exclusive lock\n");
        exit(0);
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
    fl.l_type = F_UNLCK; 
    printf("File has been unlocked\n");

    fsize = lseek(fd,0,SEEK_END);
    offset = fsize - 50;

    lseek(fd, offset, SEEK_SET);

    read(fd, buff, 50);
    printf("Last 50 bytes of the file is \n");
    printf("\n");
    printf("%s\n", buff);

    return 0;
}