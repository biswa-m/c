// Blocking Signals from OS

#include <stdio.h>
#include <signal.h>
#include <string.h>

void sighandler(int);

int main()
{
	char buffer[80] = "\0";
	sigset_t block;

	signal(SIGTERM, sighandler);
	signal(SIGINT, sighandler);
	signal(SIGCONT, sighandler);

	sigemptyset(&block); // to empty a sigset_t variable
	sigaddset(&block, SIGTERM); 
	sigaddset(&block, SIGINT);

	sigprocmask(SIG_BLOCK, &block, NULL);

	while (strcmp(buffer, "n") != 0) {
		printf("Enter a String\n");
		scanf(" %s",buffer);
		puts(buffer);
	}

	sigprocmask(SIG_UNBLOCK, &block, NULL);

	while (1)
		printf("\rProgram Running..");

	return 0;
}

void sighandler (int signum)
{
	switch (signum) {
		case SIGTERM:
			printf("SIGTERM Received\n");
			break;
		case SIGINT:
			printf("SIGINT Received\n");
			break;
		case SIGCONT:
			printf("SIGCONT Received\n");
			break;
	}
}
