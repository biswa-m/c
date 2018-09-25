// Understanding fork()

#include <stdio.h>
#include <unistd.h>

int main()
{
	int pid, n = 0;
	pid = fork();	

	printf("%d\n%d\n", pid, ++n);
}
