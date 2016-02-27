/*
 * TP1_Exe3.cpp
 *
 *  Created on: 5 févr. 2016
 *      Author: Quincy
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int nShareVar;
void* print_message(void* ptr);

int main(int argc, char* argv[])
{
	pthread_t th1, th2;
	const char* msg1 = "Thread 1";
	const char* msg2 = "Thread 2";
	nShareVar = 0;
	int r1 = pthread_create(&th1, NULL, print_message, (void*)msg1 );
	int r2 = pthread_create(&th2, NULL, print_message, (void*)msg2 );
	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	sleep(10);
	return 0;
}

void* print_message(void* ptr)
{
	srand(time(0));
	char* msg = (char*) ptr;
	while(1)
	{
		nShareVar++;
		sleep(rand()%2);
		printf("%s has value=%d \n", msg, nShareVar);
	}
	return NULL;
}
