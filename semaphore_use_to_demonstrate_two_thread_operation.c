/*************************************************************************
 * FILE		: semaphore_use_to_demonstrate_two_thread_operation().c
 * DESCRIPTION	: Program to demonstrate the use of two threads. Arbitary
 * 		  increment and decrement global value with threads.
 * AUTHOR	: GLADSON HANSDA
 * DATED	: 22/07/2020
 * **********************************************************************/

#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<stdlib.h>

#define NITER 1000000

int cnt=0;

void* Count(void* a)
{
	int i,tmp;
	for(i=0;i<NITER;i++)
	{
		tmp=cnt;	/*copy the global cnt locally*/
		tmp=tmp+1;	/*increment the local copy*/
		cnt=tmp;	/*store the local value into the global cnt*/
	}
}

int main(int argc,char* argv[])
{
	pthread_t tid1,tid2;

	if(pthread_create(&tid1,NULL,Count,NULL))
	{
		printf("\nERROR creating thread 1\n");
		exit(-1);
	}

	if(pthread_create(&tid2,NULL,Count,NULL))
	{
		printf("\nERROR creating thread 2\n");
		exit(-1);
	}

	if(pthread_join(tid1,NULL))	/*wait for the thread 1 to finish*/
	{
		printf("\nERROR joining thread1\n");
		exit(-1);
	}

	if(pthread_join(tid2,NULL))	/*wait for the thread 2 to finish*/
	{
		printf("\nERROR joining thread2\n");
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

	return 0;
}
