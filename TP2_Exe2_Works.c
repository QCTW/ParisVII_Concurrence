/*
 * TP2_Exe2.cpp
 *
 *  Created on: 12 févr. 2016
 *      Author: Quincy
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int counter;
void* print_message(void* ptr);
pthread_mutex_t verrou;

int main(int argc, char* argv[])
{
	pthread_t tProducer, tConsumer1, tConsumer2;
	const char* msg1 = "Producer";
	const char* msg2 = "Consumer A";
	counter = 0;
	pthread_mutex_init(&verrou, NULL);
	int r1 = pthread_create(&tProducer, NULL, print_message, (void*)msg1 );
	int r2 = pthread_create(&tConsumer1, NULL, print_message, (void*)msg2 );
	pthread_join(tProducer, NULL);
	pthread_join(tConsumer1, NULL);
	return 0;
}

void* print_message(void* ptr)
{
	srand(time(0));
	char* msg = (char*) ptr;
	while(1)
	{
		if(msg[0]=='P') //Producer
		{
			pthread_mutex_lock(&verrou);
			while(counter<=0)
			{
				counter++;
				printf("%s produced %d\n", msg, counter);
			}
			pthread_mutex_unlock(&verrou);
			sleep(rand()%2);
		}
		else //Consumer
		{
			pthread_mutex_lock(&verrou);
			while(counter>0)
			{
				counter--;
				printf("%s consumed %d\n", msg, counter);
			}
			pthread_mutex_unlock(&verrou);
			sleep(rand()%4);
		}
	}
	return NULL;
}
