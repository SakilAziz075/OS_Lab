#include <stdlib.h>
#include <stdio.h>
#include <sys/shm.h>
#include <string.h>
#include <unistd.h>

int main(){
    void *shared_memory;
    char buffer[100];
    int shmid;
    shmid = shmget((key_t)1122,1024,0666|IPC_CREAT);
    printf("Identify of the shared memory is : %d\n" , shmid);
    shared_memory = shmat(shmid , NULL ,0);
    printf("Proces attached at %p\n" , shared_memory);
    printf("Enter some data to write to the shared memory segment\n");

    printf("**************************\n");

    read(0,buffer,100);
    strcpy(shared_memory,buffer);
    printf("You Wrote: %s\n",(char*)shared_memory);
    

}