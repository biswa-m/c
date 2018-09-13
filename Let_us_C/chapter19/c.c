//Write a program to add the contents of one file at the end of another.

#include <stdio.h>

int main()
{
	FILE *f_source, *f_target;
	char buffer[64], source[] = "sample_files/sample1.txt",
	     target[] = "sample_files/sample2.txt";

	f_source = fopen(source, "r");
	if (f_source == NULL)
	{
		printf("Can not open source file\n");
		return 1;
	}

	f_target = fopen(target, "a");
	if (f_target == NULL)
	{
		printf("Can not open target file\n");
		return 2;
	}

	while(fgets(buffer, sizeof(buffer), f_source) != NULL)
	{
		fputs(buffer, f_target);
	}
	printf("The file %s is appended to %s\n", source, target);
	
	fclose(f_source);
	fclose(f_target);
	return 0;
}
