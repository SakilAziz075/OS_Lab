#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg_buffer
{
    long msg_type;
    char msg_text[100];
} message;

int main()
{
    int msg_id;
    int running = 1;
    msg_id = msgget((key_t)98765, 0666 | IPC_CREAT); // Connect to the message queue

    if (msg_id < 0)
    {
        printf("msgget failed");
        exit(0);
    }
    
    while (running)
    {
        // Set message type and read message from user
        message.msg_type = 1;
        printf("Enter message: ");
        fgets(message.msg_text, 100, stdin);
        message.msg_text[strcspn(message.msg_text, "\n")] = 0;

        // Send message to message queue
        msgsnd(msg_id, &message, sizeof(message.msg_text), 0);
        // Exit condition if message is exit
        if (strncmp(message.msg_text, "exit", 4) == 0)
        {
            printf("Client exiting.\n");
            running = 0;
        }
    }

    return 0;
}
