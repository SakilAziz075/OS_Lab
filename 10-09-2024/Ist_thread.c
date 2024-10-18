#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>

int i , j;

void *thread_func(void *arg)
{
	printf("inside the thread\n");
	for(j=1; j<5 ; j++)
	{
		printf("%d\n" ,j);
		sleep(1);
	}

}


int main()
{
	pthread_t p ; //thread Declaration
	pthread_create(&p, NULL ,thread_func , NULL);
	//pthread_join(p,NULL);

	printf("Inside the main programme\n");
	for(i = 20 ; i < 25 ; i++)
	{	
		printf("%d\n",i);
		sleep(1);
	}


	return 0;
}
