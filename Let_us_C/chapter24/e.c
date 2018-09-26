// Block the SIGTERM signal during execution of the SIGINT signal.

#include <stdio.h>
#include <signal.h>
#include <string.h>

void sighandler(int);

int main()
{
	signal(SIGINT, sighandler);

	while (1)
		printf("\rProgram Running..");

	return 0;
}

void sighandler (int signum)
{
	sigset_t block;
	sigemptyset(&block); // to empty a sigset_t variable
	sigaddset(&block, SIGTERM); 

	sigprocmask(SIG_BLOCK, &block, NULL);

	int i = 1000000;
	while (i > 0)
		printf("\nProcessing Interrupt %d", --i);

	sigprocmask(SIG_UNBLOCK, &block, NULL);
}
