/* Write a program that merges lines alternately from two files
and writes the results to new file. If one file has less number
of lines than the other, the remaining lines from the larger file
should be simply copied into the target file.*/

#include <stdio.h>

#define SOURCE1 "sample_files/sample3.txt"
#define SOURCE2 "sample_files/sample4.txt"
#define TARGET "sample_files/target.txt"

int main()
{
	FILE *f_s1, *f_s2, *f_t;
        char ch; 
	int line = 1;

	//file pointer initialization
        f_s1 = fopen(SOURCE1, "r");
        if (f_s1 == NULL)
        {
                printf("Can not open 1st source file\n");
                return 1;
        }

        f_s2 = fopen(SOURCE2, "r");
        if (f_s2 == NULL)
        {
                printf("Can not open 2nd source file\n");
                return 2;
        }

        f_t = fopen(TARGET, "w");
        if (f_t == NULL)
        {
                printf("Can not open target file\n");
                return 3;
        }

	//main program
	while(1)
	{
		switch (line)
		{
		case 1://print single line from source 1. 
			while((ch=fgetc(f_s1)) != '\n' && ch != EOF)
				fputc(ch, f_t);
			
			if (ch == '\n')
			{
				fputc(ch, f_t);
				line = 2;
			}
			else
				line = 4;
			
			continue;

		case 2://print single line from source 2.
			while((ch=fgetc(f_s2)) != '\n' && ch != EOF) 
				fputc(ch, f_t);

			if (ch == '\n')
			{
				fputc(ch, f_t);
				line = 1;
			}
			else
				line = 3;
			
			continue;

		case 3://print remaining lines from source 1.
			while((ch=fgetc(f_s1)) != EOF)
				fputc(ch, f_t);
			break;	
			
		case 4://print remaining lines from source 2.
			while((ch=fgetc(f_s2)) != EOF) 
				fputc(ch, f_t);
			break;
		}
		break;
	}
	return 0;
}
