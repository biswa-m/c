/* Write a program to read a file and display contents 
 * with its line numbers */

#include <stdio.h>

int main()
{
	int line = 0;
	char ch;
	FILE *fp;

	fp = fopen("sample_files/sample1.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		return 1;
	}

	if ((ch = fgetc(fp)) != EOF)
	{
		printf("%d. %c",++line, ch);
		if (ch == '\n')
			printf("%d. ", ++line);
	}
	else
		printf("The file is empty\n");

	while ((ch = fgetc(fp)) != EOF)
	{
		putchar(ch);
		if ((ch == '\n') && (fgetc(fp) != EOF))
		{
			printf("%d. ", ++line);
			fseek(fp, -1, SEEK_CUR);
		}
	}

	fclose(fp);

	return 0;
}
