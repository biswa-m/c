#include <stdio.h>
int main()
{
	char fname[] = "Myfile.txt", c;
	FILE *fp;
	fp = fopen (fname, "r");
	if (fp == NULL)
		printf("\nUnable to open file");
	while((c = getc(fp)) != EOF )
	{
		putchar(c);
	}
}
