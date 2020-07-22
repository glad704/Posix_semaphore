/**************************************************************************
 * FILE		: correction_semaphore_use_to_demonstrate_two_thread_operation.c
 * DESCRIPTION	: Program to demonstrate the use of two thread opeartion and
 * 		  work arbitrary to produce desired output each time.
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 22/07/2020
 * ***********************************************************************/

#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<stdlib.h>

#define NITER 1000000

sem_t mutex;

int cnt=0;

void* Count(void* a)
{
	sem_wait(&mutex);
	int i,tmp;
	for(i=0;i<NITER;i++)
	{
		tmp=cnt;	/*copy the global cnt locally*/
		tmp=tmp+1;	/*increment the local copy*/
		cnt=tmp;	/*store the local value into the global cnt*/
	}
	sem_post(&mutex);
}

int main(int argc,char* argv[])
{
	sem_init(&mutex,0,1);
	pthread_t tid1,tid2;

	if(pthread_create(&tid1,NULL,Count,NULL))
	{
		printf("\nERROR creating thread 1\n");
		exit(-1);
	}

	if(pthread_create(&tid2,NULL,Count,NULL))
	{
		printf("ERROR creating thread 2\n");
		exit(-1);
	}

	if(pthread_join(tid1,NULL))	/*wait for thread 1 to finish*/
	{
		printf("\nERROR joining thread 1\n");
		exit(-1);
	}

	if(pthread_join(tid2,NULL))	/*wait for thread 2 to finish*/
	{
		printf("\nERROR joining thread 2\n");
		exit(-1);
	}

	if(cnt<2*NITER)
	{
		printf("\nBOOM! cnt is [%d], should be %d\n",cnt,2*NITER);
	}
	else
	{
		printf("\nOK! cnt is [%d]\n",cnt);
	}

	pthread_exit(NULL);
}
