#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
    pid_t pid, gpid;
    int child_count = 0;
    int grandchild_count = 0;

    pid = fork(); // First fork to create a child process
    if (pid < 0) {
        perror("Failed to fork");
        exit(1); // Exit with an error code
    } else if (pid == 0) {
        // Child process
        printf("Child Process: PID = %d, PPID = %d\n", getpid(), getppid());
        child_count++;

        gpid = fork(); // Fork again to create a grandchild
        if (gpid < 0) {
            perror("Failed to fork");
            exit(1); // Exit with an error code
        } else if (gpid == 0) {
            // Grandchild process
            printf("Grandchild Process: PID = %d, PPID = %d\n", getpid(), getppid());
            printf("Displaying Roll Number: 123456\n"); // Replace with actual roll number
            exit(0); // Successful termination of grandchild
        } else {
            // Child waits for grandchild to finish
            wait(NULL);
            grandchild_count++; // Increment grandchild count after it has been created
            printf("Child Process: Total number of grandchild processes created: %d\n", grandchild_count);
            exit(0); // Successful termination of child
        }
    } else {
        // Parent process
        printf("Parent Process: PID = %d\n", getpid());
        printf("Waiting for child to finish...\n");
        wait(NULL); // Wait for the child process to finish

        child_count = 1; // Only one direct child
        printf("Total number of child processes created: %d\n", child_count);
        printf("Total number of grandchild processes created: %d\n", grandchild_count);
        exit(0); // Successful termination of parent
    }
}
