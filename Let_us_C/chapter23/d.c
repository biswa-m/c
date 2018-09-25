/* Understanding fork. 
 * Code to get exit code of child process for proper cleanup
 */

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main()
{
	unsigned int i = 0;
	int pid, status;
	
	pid = fork();

	if (pid == 0) {
		sleep(5);
		printf("The child is now terminating\n");
	} else {
		waitpid(pid, &status, 0);
		if(WIFEXITED(status))
			printf("Parent: Child terminated normally\n");
		else
			printf("Parent: Child terminated abnormally\n");
	}
	return 0;
}
