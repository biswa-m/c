#include <stdio.h>
#include <stdlib.h>

int main()
{
	FILE *fp;
	char c;
	fp = fopen ("Myfile.txt", "r");
	if(fp == NULL)
	{
		puts("Can not open file\n");
		exit(1);
	}
	while ((c = getc(fp)) != EOF)
		putchar(c);
	fclose(fp);
	return 0;
}
