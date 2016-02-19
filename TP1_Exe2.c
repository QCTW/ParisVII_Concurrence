/*
 *TP1_Exe2.cpp
 *
 *Createdon:5févr.2016
 *Author:Quincy
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

int main()
{
	int x=0;
	int pid = fork();
	printf("Valeur de fork = %d\n", pid);
	printf("Processus %d de pere %d\n", (int) getpid(), (int) getppid() );
	if (pid==0)
	{
		x=25;
		printf("Valeur de x pour le fils: %d\n", x);
		printf("Fin du processus fils\n");
	}
	else
	{
		while (x!=25)
		{
			sleep(2);
			printf("Valeur de x pour le pere: %d\n",x);
		}
		printf("Fin du processus pere\n");
	}
	return 0;
}
