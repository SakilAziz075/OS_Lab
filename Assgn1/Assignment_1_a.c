#include<unistd.h>
#include<stdio.h>
#include<sys/types.h>

int main()
{
    int count_process=1;
    int count_childp=0;
    int count_grandchildp=0;
    pid_t pid,mypid,myppid;
    printf("Before creating child process\n");
    printf("The process id : %d\n",getpid());
    printf("----------------------------------\n");
    pid=fork();

    if(pid<0) 
    {
        printf("Fail to create child process\n");
        return 1;
    }
    
    if (pid == 0) 
    {
        pid_t q;
        count_process+=1;
        count_childp+=1;
        printf("Child process is created \n");
        mypid=getpid();
        myppid=getppid();
        printf("The process child id : %d and parent id : %d\n",mypid,myppid);
        printf("----------------------------------\n");

        q=fork();
        if (q==0) 
        {
            count_process+=1;
            count_childp+=1;
            count_grandchildp+=1;
            printf("----------------------------------\n");
            printf("Grandchild is created\n");
            mypid=getpid();
            myppid=getppid();
            printf("The grandchild process id : %d and parent id : %d\n",mypid,myppid);
            printf("----------------------------------\n");
            printf("My Roll No is CSB22012\n"); 
            printf("----------------------------------\n");
        } 

        else 
        {
            mypid=getpid();
            printf("Inside the parent process: %d \n",mypid);
        }

        printf("The number of process is %d\n",count_process);
        printf("The number of child process is %d\n",count_childp);
        printf("The number of grandchild process is %d\n",count_grandchildp);
        return 0;
    }
}