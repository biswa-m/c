#include <stdio.h>

int main()
{
	FILE *fp;
	char name[20];
	int i;

	fp = fopen("Myfile1.txt", "w");
	for (i=0; i<=10; i++)
	{
		puts("\nEnter name");
		scanf("%s", name);
		fwrite(name, sizeof(name), 1, fp);
	}
	fclose (fp);

	fp = fopen("Myfile1.txt", "r");
	while(fread(&name, sizeof(name),1,fp) == 1)
		printf("%s ", name);
}
