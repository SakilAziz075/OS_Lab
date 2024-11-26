#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

void signal_handler(int sig) // to handle signal
{
        printf("Received signal: %d \n", sig);
        // Check if the signal is SIGINT (Interrupt from keyboard  Ctrl+C)
        if (sig == SIGINT)
        {
                pid_t pid = fork(); // create a child process

                if (pid == -1)
                {
                        printf("fork failed");
                        exit(1);
                }

                else if (pid == 0)
                {
                        printf("Child process: PID = %d, Parent PID = %d\n", getpid(), getppid());
                        exit(0);
                }

                else
                {
                        printf("Parent process: PID = %d, Child PID = %d\n", getpid(), pid);
                }
        }
}

int main()
{
        signal(SIGINT, signal_handler);  // Interrupt from keyboard (usually Ctrl+C)
        signal(SIGKILL, signal_handler); // Kill signal (can’t be caught, blocked, or ignored)
        signal(SIGTERM, signal_handler); // Termination signal
        signal(SIGQUIT, signal_handler); // Quit from keyboard (usually Ctrl+\)

        while (1)
        {
                printf("Running Program 2a... Waiting for signals.\n");
                sleep(3); // Sleep for 3 seconds
        }

        return 0;
}
