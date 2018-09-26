/* Exercise from "Let us C", chapter 24
 *
 * Write a program to handle the SIGINT and SIGTERM signals.
 * From inside the handler for SIGINT signal write an infinite 
 * loop to print the message ‘Processing Signal’. Run the 
 * program and make use of Ctrl + C more than once. Run the 
 * program once again and press Ctrl + C once then use the kill
 * command. What are your observations?
 */

#include <stdio.h>
#include <signal.h>
#include <string.h>

void sighandler(int);

int main()
{
	signal(SIGTERM, sighandler);
	signal(SIGINT, sighandler);

	while (1)
		printf("\rProgram Running..");

	return 0;
}

void sighandler (int signum)
{
	unsigned int i = 0u;

	switch (signum) {
		case SIGTERM:
			printf("SIGTERM Received\n");
			break;
		case SIGINT:
			printf("SIGINT Received\n");
			while (1)
				printf("\r%u - Processing Signal", ++i);
			break;
	}
}
