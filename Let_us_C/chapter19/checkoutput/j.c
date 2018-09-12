#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fp;

	fp = open("students.c", O_RDONLY);

	if (fp == -1)
		puts("cannot open file");
	else
		close(fp);
}
