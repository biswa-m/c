#include <stdio.h>

int main()
{
	FILE *fp;
	char name[25];
	int age;

	fp = fopen("Myfile.txt", "r");

	while (fscanf(fp, "%s %d", name, &age) != EOF)
		printf("%s %d\n", name, age);
	
	fclose(fp);
}
