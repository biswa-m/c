// write only even lines from a file to a new one.
// also display the even lines

#include <stdio.h>

int main()
{
	FILE *fsource, *ftarget;
	char ch;
	int even = 0;

	fsource = fopen("sample_files/sample1.txt", "r");
	if (fsource == NULL)
	{
		printf("Can not open source file\n");	
		return 1;
	}

	ftarget = fopen("sample_files/sample2.txt", "w");
	if (ftarget == NULL)
	{
		printf("Can not open target file\n");
		return 2;
	}

	while((ch = fgetc(fsource)) != EOF)
	{
		if (ch == '\n')
		{
			if (even == 1 )
			{
				fputc(ch, ftarget);
				printf("%c", ch);
			}
			even = !even;
		}
		else if (even == 1)
		{
			fputc(ch, ftarget);
			printf("%c", ch);
		}
	}
	
	return 0;
}
