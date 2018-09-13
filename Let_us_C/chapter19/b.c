/* Write a program to find the size of a text file without
*  traversing it character by character */

#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
	char buffer[128];
	int count = 0;

	fp = fopen("sample_files/sample1.txt", "r");
	if (fp == NULL)
	{
		printf("Can not open file\n");
		return 1;
	}

	while(fgets(buffer, 128, fp) != NULL)
	{
		count += strlen(buffer);
	}
	printf("The total character size of the file is %d\n", count);

	return 0;
}
