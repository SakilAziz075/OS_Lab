#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
struct msg_buffer
{
    long msg_type;
    char msg_text[100];
} message;

int main()
{
    int msg_id;
    int running = 1;
    // Create message queue and return ID
    msg_id = msgget((key_t)98765, 0666 | IPC_CREAT);
    if (msg_id < 0)
    {
        printf("msgget failed");
        exit(0);
    }

    // Print the message queue ID to stderr
    fprintf(stderr, "Message Queue ID: %d\n", msg_id);

    while (running)
    {

        // Receive messages
        msgrcv(msg_id, &message, sizeof(message.msg_text), 1, 0);
        printf("Received Message: %s\n", message.msg_text);

        // Exit condition if message is exit
        if (strncmp(message.msg_text, "exit", 4) == 0)
        {
            printf("Server exiting.\n");
            running = 0;
        }
    }

    // Destroy the message queue
    msgctl(msg_id, IPC_RMID, NULL);

    return 0;
}