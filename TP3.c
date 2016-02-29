/*
 * TP3.c
 *
 *  Created on: 19 févr. 2016
 *      Author: Quincy
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int numOfPassengersOnBus;
int flag;
void* print_message(void* ptr);
pthread_cond_t condFull, condAvailable;
pthread_mutex_t lock;

int main(int argc, char* argv[])
{
	pthread_cond_init(&condFull, NULL);
	pthread_cond_init(&condAvailable, NULL);
	pthread_mutex_init(&lock, NULL);
	pthread_t tProducer, tConsumer1, tConsumer2;
	const char* msg1 = "Producer";
	const char* msg2 = "Consumer_A";
	const char* msg3 = "Consumer_B";
	numOfPassengersOnBus = 0;
	int r1 = pthread_create(&tProducer, NULL, print_message, (void*)msg1 );
	sleep(1);
	int r2 = pthread_create(&tConsumer1, NULL, print_message, (void*)msg2 );
	sleep(1);
	int r3 = pthread_create(&tConsumer2, NULL, print_message, (void*)msg3 );
	sleep(1);
	pthread_join(tProducer, NULL);
	pthread_join(tConsumer1, NULL);
	pthread_join(tConsumer2, NULL);
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
			pthread_mutex_lock(&lock);
			while(flag)
			{
				printf("%s waits flag to become 0...\n", msg);
				pthread_cond_wait(&condFull, &lock);
				printf("%s is waken.\n", msg);
			}

			int oldVal = numOfPassengersOnBus;
			numOfPassengersOnBus++;
			printf("%s %d=>%d with flag = %s\n", msg, oldVal, numOfPassengersOnBus, flag?"1":"0");
			flag=1;
			printf("%s wakes up sleeping threads with flag = 1.\n", msg);
			pthread_cond_broadcast(&condAvailable);
			pthread_mutex_unlock(&lock);
			sleep(rand()%2);
		}
		else //Consumer
		{
			pthread_mutex_lock(&lock);
			while(!flag)
			{
				printf("%s waits flag to become 1...\n", msg);
				pthread_cond_wait(&condAvailable, &lock);
				printf("%s is waken.\n", msg);
			}

			int oldVal = numOfPassengersOnBus;
			numOfPassengersOnBus--;
			printf("%s %d=>%d with flag = %s\n", msg, oldVal, numOfPassengersOnBus, flag?"1":"0");
			flag = 0;
			printf("%s wakes up sleeping threads with flag = 0.\n", msg);
			pthread_cond_broadcast(&condFull);
			pthread_mutex_unlock(&lock);
			sleep(rand()%4);
		}
	}
	return NULL;
}
