#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <sys/types.h>

int pipe_fd[2];  // Pipe file descriptors

void generate_fibonacci(int n, int *fib_series) {
    fib_series[0] = 0;
    if (n > 1) fib_series[1] = 1;
    for (int i = 2; i < n; i++) {
        fib_series[i] = fib_series[i - 1] + fib_series[i - 2];
    }
}

void handle_sigint(int sig) {
    printf("SIGINT received! Creating child process...\n");

    if (pipe(pipe_fd) == -1) {
        perror("Pipe creation failed");
        exit(1);
    }

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        close(pipe_fd[0]);  // Close reading end of pipe in child

        // Send child PID to parent
        pid_t child_pid = getpid();
        write(pipe_fd[1], &child_pid, sizeof(child_pid));

        // Take input from user
        int n;
        printf("Enter the number of terms for Fibonacci series: ");
        scanf("%d", &n);

        if (n <= 0) {
            fprintf(stderr, "Number of terms must be positive.\n");
            close(pipe_fd[1]);
            exit(1);
        }

        int fib_series[n];
        generate_fibonacci(n, fib_series);

        // Send Fibonacci terms to parent
        for (int i = 0; i < n; i++) {
            write(pipe_fd[1], &fib_series[i], sizeof(fib_series[i]));
        }

        // Send a special end marker to indicate the end of the Fibonacci series
        int end_marker = -1;
        write(pipe_fd[1], &end_marker, sizeof(end_marker));

        // Send signal ID to parent
        write(pipe_fd[1], &sig, sizeof(sig));

        close(pipe_fd[1]);  // Close writing end in child
        exit(0);
    } else { // Parent process
        close(pipe_fd[1]);  // Close writing end of pipe in parent

        // Read child PID
        pid_t child_pid;
        read(pipe_fd[0], &child_pid, sizeof(child_pid));
        printf("Child Process ID: %d\n", child_pid);

        // Read and display Fibonacci terms
        int fib_term;
        printf("Fibonacci Series: ");
        while (read(pipe_fd[0], &fib_term, sizeof(fib_term)) > 0) {
            if (fib_term == -1) break;  // Stop when end marker is read
            printf("%d ", fib_term);
        }
        printf("\n");

        // Read and display signal ID
        int signal_id;
        read(pipe_fd[0], &signal_id, sizeof(signal_id));
        printf("Signal ID received in parent: %d\n", signal_id);

        close(pipe_fd[0]);  // Close reading end in parent
    }
}

int main() {
    // Set up the SIGINT handler
    signal(SIGINT, handle_sigint);

    // Wait for SIGINT (CTRL+C)
    printf("Press CTRL+C to trigger the signal handler...\n");
    while (1) {
        pause();  // Wait indefinitely for a signal
    }

    return 0;
}
