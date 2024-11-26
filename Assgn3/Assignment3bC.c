#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#define FIFO_PATH "/tmp/myfifo"
#define BUFFER_SIZE 1024
#define ACK_MESSAGE "ACKNOWLEDGEMENT: Message received"

int main() {
    char buffer[BUFFER_SIZE];
    int fifo_fd;

    // Create the FIFO with read and write permissions for all users
    if (mkfifo(FIFO_PATH, 0666) == -1) {
        if (errno != EEXIST) { // If the error is something other than "file exists"
            perror("Error creating FIFO");
            exit(EXIT_FAILURE);
        }
    }

    printf("Server: Waiting for messages from Client...\n");

    // Open the FIFO for both reading and writing
    fifo_fd = open(FIFO_PATH, O_RDWR);
    if (fifo_fd == -1) {
        perror("Error opening FIFO");
        exit(EXIT_FAILURE);
    }

    // Continuously read and write to the FIFO
    while (1) {
        // Read message from Program2 (Client)
        ssize_t bytes_read = read(fifo_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read > 0) {
            buffer[bytes_read] = '\0'; // Null terminate the string
            printf("Server received: %s\n", buffer);

            // If the message is not an acknowledgment, send an acknowledgment back to Client
            if (strcmp(buffer, ACK_MESSAGE) != 0) {
                write(fifo_fd, ACK_MESSAGE, strlen(ACK_MESSAGE));
            }
        }
    }

    // Close and remove the FIFO
    close(fifo_fd);
    unlink(FIFO_PATH);

    return 0;
}
