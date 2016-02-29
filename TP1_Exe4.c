/*
 * TP1_Exe4.cpp
 *
 *  Created on: 5 févr. 2016
 *      Author: Quincy
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int numOfPassengersOnBus;
int flag;
void* print_message(void* ptr);

int main(int argc, char* argv[])
{
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
	pthread_join(tProducer, NULL);
	pthread_join(tConsumer1, NULL);
	pthread_join(tConsumer2, NULL);
	sleep(10);
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
			while(flag);
			int oldVal = numOfPassengersOnBus;
			numOfPassengersOnBus++;
			printf("%s %d=>%d with flag %s\n", msg, oldVal, numOfPassengersOnBus, flag?"true":"false");
			flag = 1;
			sleep(rand()%2);
		}
		else
		{
			while(!flag);
			int oldVal = numOfPassengersOnBus;
			numOfPassengersOnBus--;
			printf("%s %d=>%d with flag %s\n", msg, oldVal, numOfPassengersOnBus, flag?"true":"false");
			flag = 0;
			sleep(rand()%4);
		}
	}
	return NULL;
}
