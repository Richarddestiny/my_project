#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

int lock_var = 0;
time_t end_time;

void pthread1(void *arg);
void pthread2(void *arg);

pthread_mutex_t mutex;

int main(int argc, char *argv[])
{
	pthread_t id1,id2;
	int ret;

	end_time = time(NULL)+10;
	
	/***** initialize your mutex *****/
	pthread_mutex_init(&mutex,NULL);
	
	/***** create thread 1 *****/
	ret=pthread_create(&id1,NULL,(void *)pthread1, NULL);
	if(ret!=0)
		perror("pthread cread1");
	
	/***** create thread 2 *****/
	ret=pthread_create(&id2,NULL,(void *)pthread2, NULL);
	if(ret!=0)
		perror("pthread cread2");
	
	pthread_join(id1,NULL);
	pthread_join(id2,NULL);
	
	exit(0);
}

void pthread1(void *arg)
{
	int i;
	while(time(NULL) < end_time)
	{
		if(pthread_mutex_lock(&mutex)!=0)
		{
			perror("pthread_mutex_lock");
		}
		else
			printf("pthread1:pthread1 lock the variable\n");
		
		for(i=0;i<2;i++)
		{
			sleep(1);
			lock_var++;
		}
		
		if(pthread_mutex_unlock(&mutex)!=0)
		{
			perror("pthread_mutex_unlock");
		}
		else
			printf("pthread1:pthread1 unlock the variable\n");
		
		sleep(1);
	}
}

void pthread2(void *arg)
{
	int ret;
	
	while(time(NULL) < end_time)
	{
		ret=pthread_mutex_trylock(&mutex);
		if(ret==EBUSY)
			printf("pthread2:the variable is locked by pthread1\n");
		else
		{
			if(ret!=0)
			{
				perror("pthread_mutex_trylock");
				exit(1);
			}
			else
				printf("pthread2:pthread2 got lock."
					"The variable is %d\n",lock_var);

			if(pthread_mutex_unlock(&mutex)!=0)
			{
				perror("pthread_mutex_unlock");
			}
			else
				printf("pthread2:pthread2 unlock the variable\n");
		}
		sleep(3);
	}
}
