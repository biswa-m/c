/* Understanding exec library functions
 * Execute child program which print command line arg
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	char str[2048];
	int pid, status;

	pid = fork();

	if (pid == 0) {
		execv("./prnt_arg.out", argv);
	} else {
		waitpid(pid, &status, 0);
	}

	return 0;
}
