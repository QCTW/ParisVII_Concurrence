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

int totalNumOfPassengers = 10;
int numOfPassengersOnBus = 0;
int maxPassenger = 5;
int isBusArrived = 0;

void* bus(void* ptr);
void* passenger(void* ptr);
pthread_cond_t condFull, condArrived, condEmpty, condAvailable;
pthread_mutex_t lock;

int main(int argc, char* argv[])
{
	srand(time(0));
	pthread_cond_init(&condFull, NULL); //Used to check if the bus is full e.g: numOfPassengersOnBus < maxPassenger
	pthread_cond_init(&condArrived, NULL); //Used to check if the bus is arrived e.g: isBusArrived=0 (0=pas arrive)
	pthread_cond_init(&condEmpty, NULL); //Used to check if the bus is empty e.g: numOfPassengersOnBus>0
	pthread_cond_init(&condAvailable, NULL); //Used to check if the bus has space to get in e.g:
	pthread_mutex_init(&lock, NULL);
	pthread_t tBus;
	pthread_t* tPassengers = malloc(sizeof(pthread_t)*totalNumOfPassengers);
	const char* busMsg = "Bus";
	pthread_create(&tBus, NULL, bus, (void*)busMsg );
	for(int i=0; i<totalNumOfPassengers; i++)
	{
		pthread_create(&tPassengers[i], NULL, passenger, NULL );
	}
	sleep(1);
	pthread_join(tBus, NULL);
	for(int i=0; i<totalNumOfPassengers; i++)
	{
		pthread_join(tPassengers[i], NULL);
	}
	return 0;
}

void* bus(void* ptr)
{
	char* tName = (char*) ptr;
	while(1)
	{
		pthread_mutex_lock(&lock);
		if(isBusArrived == 0)
		{
			isBusArrived = 1;
			printf("%s arrived with %d passengers!\n", tName, numOfPassengersOnBus);
			pthread_cond_broadcast(&condArrived);
		}

		while(numOfPassengersOnBus>0)
		{
			printf("%s waits to empty all %d passengers...\n", tName, numOfPassengersOnBus);
			pthread_cond_wait(&condEmpty, &lock);
		}
		printf("%s unloaded all passengers. Now loading new passengers.\n", tName);
		while(numOfPassengersOnBus<maxPassenger)
			pthread_cond_wait(&condFull, &lock);
		printf("%s loaded max %d passengers. Depart...\n", tName, maxPassenger);
		isBusArrived = 0;
		pthread_mutex_unlock(&lock);
		sleep(rand()%2);
	}
	return NULL;
}

void* passenger(void* ptr)
{
	static int globalId = 0; //When we declare 'static' within a method in C, it exists only when method is called and stays the same variable when
	int isOnBus = 0;
	char msg[12];
	sprintf(msg, "Passenger%d", globalId); // puts string into buffer
	globalId++;
	while(1)
	{
		pthread_mutex_lock(&lock);
		while(isBusArrived==0)
		{
			printf("%s waits the bus to arrive...\n", msg);
			pthread_cond_wait(&condArrived, &lock);
		}

		if(numOfPassengersOnBus==0)
		{
			pthread_cond_broadcast(&condEmpty);
			printf("%s notified that the bus is empty!\n", msg);
		}

		if(isOnBus==0)
		{
			while(numOfPassengersOnBus==maxPassenger)
			{
				printf("%s waits the bus to have space...\n", msg);
				pthread_cond_wait(&condAvailable, &lock);
			}
			numOfPassengersOnBus++; //Get into the bus
			printf("%s got into the bus. Total passengers now = %d.\n", msg, numOfPassengersOnBus);
			isOnBus=1;
		}
		else
		{
			while(isBusArrived==0)
			{
				printf("%s is on the bus and wait to his destination...\n", msg);
				pthread_cond_wait(&condArrived, &lock);
			}
			numOfPassengersOnBus--; //Get of the bus
			printf("%s got off the bus. Total passengers now = %d.\n", msg, numOfPassengersOnBus);
			isOnBus = 0;
			pthread_cond_broadcast(&condAvailable);
		}

		if(numOfPassengersOnBus==maxPassenger)
		{
			pthread_cond_broadcast(&condFull);
			printf("%s notified that the bus is full!\n", msg);
		}
		pthread_mutex_unlock(&lock);
		sleep(rand()%maxPassenger); //Wait for the target station which takes (rand()%maxPassenger) time to arrive
	}
	return NULL;
}
