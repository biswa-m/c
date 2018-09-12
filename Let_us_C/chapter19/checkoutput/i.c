#include <stdio.h>
#include <fcntl.h>

int main()
{
	int fp;
	fp = open("pr22.c", O_CREAT, 200);

	if (fp == -1)
		puts("Can not open file");
	else 
		close (fp);
}
