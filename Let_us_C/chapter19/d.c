/*Suppose a file contains student’s records with each record
* containing name and age of a student. Write a program to read
* these records and display them in sorted order by name.*/

#include <stdio.h>
#include <string.h>

int main()
{
	FILE *fp;
	int i = 0, j, k;
	struct student
	{
		char name[50];
		int age;
	};
	struct student record[200];

	fp = fopen("sample_files/student.txt", "r");
	if (fp == NULL)
	{
		printf("Cannot open file\n");
		return 1;
	}

	printf("The stored records are as below\n");
	while(fscanf(fp, "%s %d", record[i].name, &record[i].age) != -1)
	{
		printf("%s\t%d\n", record[i].name, record[i].age);
		++i;
	}

	//sorting by name
	for (j = 0; j < i-1; ++j)
	{
		for (k = 1; k < i-j; ++k)
		{
			if (strcmp(record[k-1].name, record[k].name) > 1)
			{
				record[i+1] = record[k-1];
				record[k-1]   = record[k];
				record[k]   = record[i+1];			
			}
		}
	}

	printf("\nThe records are sorted by name\n");
	for (j = 0; j < i; ++j)
		printf("%s\t%d\n", record[j].name, record[j].age);

	fclose(fp);
	return 0;	
}
