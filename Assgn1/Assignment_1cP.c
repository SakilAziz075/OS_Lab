#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid;
    int status;

    // Create child process
    pid = fork();

    if (pid == -1) {
        // Error in creating child process
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) {
        // Child Process: Execute a new program (child_program)
        char *args[] = {"./Assignment_1cC", "Hello", "World", NULL};
        
        // Using execv() to overlay the current program with a new one
        execv(args[0], args);

        // If execv() fails
        perror("Execv failed");
        exit(1);
    }
    
     else 
     {
        // Parent Process: Wait for the child to finish
        waitpid(pid, &status, 0);

        // Check if child exited normally
        if (WIFEXITED(status)) 
        {
            printf("Child process exited with status %d\n", WEXITSTATUS(status));
        } 
        else 
        {
            printf("Child process did not exit normally\n");
        }
    }

    return 0;
}
