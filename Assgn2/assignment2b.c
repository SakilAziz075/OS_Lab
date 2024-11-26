#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main() 
{
        pid_t pid;
        int sig;

        printf("Enter Process ID: ");
        scanf("%d", &pid);
        printf("Enter Signal ID: ");
        scanf("%d", &sig);

// Send the specified signal to the specified process
        
        if (kill(pid, sig) == -1) 
        {
                printf("Failed to send signal");
                exit(1);
        } 
        else 
        {
                printf("Signal %d sent to process %d\n", sig, pid);
        }

        return 0;
}
