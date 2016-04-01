/*
 * TP1_Exe5.cpp
 *
 *  Created on: 5 févr. 2016
 *      Author: Quincy
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int flag1, flag2;
void* print_message(void* ptr);

int main(int argc, char* argv[])
{
	flag1 = 1;
	flag2 = 1;
	pthread_t tProducer, tConsumer;
	const char* msg1 = "A_Thread";
	const char* msg2 = "B_Thread";
	int r1 = pthread_create(&tProducer, NULL, print_message, (void*)msg1 );
	sleep(1);
	int r2 = pthread_create(&tConsumer, NULL, print_message, (void*)msg2 );
	sleep(1);
	pthread_join(tProducer, NULL);
	pthread_join(tConsumer, NULL);
	sleep(10);
	return 0;
}

void* print_message(void* ptr)
{
	srand(time(0));
	char* msg = (char*) ptr;
	while(1)
	{
		if(msg[0]=='A')
		{
			while(!flag1)
			{
				printf("%s waits flag1 to change to true\n", msg);
				sleep(1);
			}

			flag1 = 0;
			printf("%s changed flag1 true->false\n", msg);

			while(!flag2)
			{
				printf("%s waits flag2 to change to true\n", msg);
				sleep(1);
			}

			flag2 = 0;
			printf("%s changed flag2 true->false\n", msg);
		}
		else
		{
			while(flag1)
			{
				printf("%s waits flag1 to change to false\n", msg);
				sleep(1);
			}

			flag1 = 1;
			printf("%s changed flag1 false->true\n", msg);

			while(flag2)
			{
				printf("%s waits flag2 to change to false\n", msg);
				sleep(1);
			}
			flag2 = 1;
			printf("%s changed flag2 false->true\n", msg);
		}
	}
}
