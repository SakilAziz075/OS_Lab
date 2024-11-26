#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
void *thread_function(void *arg);

int main()
{
        pthread_t p;                                     // thread declaration
        pthread_create(&p, NULL, thread_function, NULL); // thread creation
        pthread_join(p, NULL);                           // process waits for thread to finish
        printf("This is main function\n");
}

void *thread_function(void *arg) // work to be done by thread is defined in this function
{
        printf("Hello World\n");
        pthread_exit(NULL); // terminate the thread
}