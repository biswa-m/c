// Getting familiar with signal()

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

void sighandler(int signum)
{ 
	printf("\nSignal Interrupt %d Recieved \nTerminating...", signum);
	exit(1);
}

int main()
{
	signal(SIGINT, (void *)sighandler);	

	while(1)
		printf("Program Running.. \t");

	return 0;
}
