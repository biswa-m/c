/* Understanding fork and exec.
 * Executing a program on the disk as part of child process
 */

#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid;
	pid = fork();

	if (pid == 0) {
		execl("/home/neo/c/Let_us_C/chapter20/./a.out", "","b.c", NULL);
		
		printf("After exec(). This printf() is not going to execute");
	} else {
		printf("Parent process\n");
	}
	return 0;
}
