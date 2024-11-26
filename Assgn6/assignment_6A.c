#include <stdio.h> 
#include <stdlib.h>
#include <sys/shm.h>
#include <string.h>

int main(){
    void *shared_memory;
    char buffer[100];
    int shmid;
    shmid = shmget((key_t)1122,1024,0666);
    printf("key of the Shared Memory is: %d\n",shmid);
    shared_memory= shmat(shmid,NULL,0);
    printf("Process attached at %p\n", shared_memory);
    printf("Data read from shared Memory is: %s \n" , (char*)shared_memory);
}
