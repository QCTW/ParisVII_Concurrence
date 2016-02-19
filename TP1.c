#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void* print_message1(void* ptr);
void* print_message2(void* ptr);
void* print_message3(void* ptr);
void* print_message(void* ptr);

int main(int argc, char* argv[])
{
	pthread_t th1, th2, th3;
	const char* s1="I am thread 1";
	const char* s2="I am thread 2";
	const char* s3="I am thread 3";

	pthread_t threads[10];
	for(int i=0; i<10; i++)
	{
		printf("%s %d\n", "Create inter thread", i);
		char* s = (char*) "I am thread iter";
		char* msg = (char*) malloc(100);
		sprintf(msg, "%s %d", s, i);
		int r = pthread_create(&threads[i], NULL, print_message, (void*)msg );
	}

//	for(int i=0; i<10; i++)
//	{
//		pthread_join(threads[i], NULL);
//	}

	int r1=pthread_create(&th1, NULL, print_message1, (void*)s1 );
	int r2=pthread_create(&th2, NULL, print_message2, (void*)s2 );
	int r3=pthread_create(&th3, NULL, print_message3, (void*)s3 );

//	pthread_join(th1, NULL);
//	pthread_join(th2, NULL);
//	pthread_join(th3, NULL);

	sleep(10);
	return 0;
}

void* print_message(void* ptr)
{
	char* msg = (char*) ptr;
	while(1)
	{
		sleep(1);
		printf("%s \n", msg);
	}
	return NULL;
}

void* print_message1(void* ptr)
{
	char* msg = (char*) ptr;
	while(1)
	{
		sleep(1);
		printf("%s \n", msg);
	}
	return NULL;
}

void* print_message2(void* ptr)
{
	char* msg = (char*) ptr;
	while(1)
	{
		sleep(1);
		printf("%s \n", msg);
	}
	return NULL;
}

void* print_message3(void* ptr)
{
	char* msg = (char*) ptr;
	while(1)
	{
		sleep(1);
		printf("%s \n", msg);
	}
	return NULL;
}
