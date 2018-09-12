#include "stdio.h"

int main()
{
	char ch;
	FILE *fp;

	fp = fopen("Myfile.txt", "r");

	while ((ch = getc(fp)) != EOF)
		printf("%c", ch);
	
	fclose(fp);
}
