#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <unistd.h>
#include <fcntl.h>

void log_time(FILE *file, const char *label) {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    fprintf(file, "%s: %ld.%06ld seconds\n", label, tv.tv_sec, tv.tv_usec);
}

int main() {
    FILE *file;
    pid_t pid;
    struct tms tms_start, tms_end;
    clock_t start_time, end_time;

    // Open the file in write mode
    file = fopen("process_times.txt", "w");
    if (file == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Log the submission time (time before fork)
    log_time(file, "Submission Time");

    // Create a child process
    pid = fork();

    if (pid < 0) {
        // Error in fork
        perror("Fork failed");
        fclose(file);
        return 1;
    }

    if (pid == 0) {
        // Child process: simulate some work by sleeping for 2 seconds
        sleep(2);

        // Log the termination time (time before child exits)
        log_time(file, "Termination Time of Child Process");
        
        // Record the times of the child process
        start_time = times(&tms_start);  // Before execution
        // Some computation or process logic
        end_time = times(&tms_end);     // After execution

        fprintf(file, "CPU Time used by Child Process: %ld ticks\n", end_time - start_time);
        fclose(file);
        exit(0);
    } else {
        // Parent process: wait for child process to terminate
        wait(NULL);
        
        // Log the termination time of the parent process
        log_time(file, "Termination Time of Parent Process");

        // Record the times of the parent process
        start_time = times(&tms_start);  // Before execution
        // Some computation or process logic
        end_time = times(&tms_end);     // After execution

        fprintf(file, "CPU Time used by Parent Process: %ld ticks\n", end_time - start_time);
        fclose(file);
    }

    return 0;
}
