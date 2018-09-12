#include <stdio.h>

int main()
{
	FILE *fp;
	char str[80];
	
	fp = fopen ("Myfile.txt", "r");
	if (fp == NULL)
		printf("Can not open\n");
	while(fgets(str, 80, fp) != NULL)
		printf("%s", str);
		//puts(str);
	fclose(fp);
}
