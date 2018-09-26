// Communucating with OS. Handaling multiple signal.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>

void inthandler()
{
	printf("\nSIGINT Received\n");
	sleep(2);
}

void termhandler()
{
	printf("\nSIGTERM Received\n");
	sleep(2);
}

void conthandler()
{
	printf("\nSIGCONT Receive\n");
	sleep(2);
}

int main()
{
	signal(SIGINT, inthandler);
	signal(SIGTERM, termhandler);
	signal(SIGCONT, conthandler);

	while(1)
		printf("\r Program Running");

	return 0;
}
