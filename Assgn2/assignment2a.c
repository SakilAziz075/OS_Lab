
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void handler(int num) 
{
    pid_t pid;

    // Create a child process using fork()
    pid = fork();

    if (pid < 0) 
    {
        printf("fork");
        exit(1);
    } 
    else if (pid == 0) 
    {
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
        exit(0);
    } 
    
    else  
    {
        printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
    }
}

int main() 
{
    // SIGINT using signal() system call
    signal(SIGINT, handler);

    // Infinite loop 
    while (1) 
    {
        printf("Running... Press Ctrl+C to generate SIGINT signal.\n");
        sleep(1); // Sleep for 1 seconds to avoid excessive CPU usage
    }
    return 0;
}
