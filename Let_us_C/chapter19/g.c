/* Write a program to display the contents of a text file on the 
 * screen. Make following provisions:
 * 
 * Display the contents inside a box drawn with opposite corner
 * co-ordinates being ( 0, 1 ) and ( 79, 23 ). Display the name of
 * the file whose contents are being displayed, and the page
 * numbers in the zeroth row. The moment one screenful of file
 * has been displayed, flash a message ‘Press any key...’ in 24 th
 * row. When a key is hit, the next page’s contents should be
 * displayed, and so on till the end of file.
 */

#include <stdio.h>
#include <stdlib.h>

#define _LENGTH 79
#define _HEIGHT 23
#define _LEFT_MERGIN (printf("%-3c", '|')) 
#define _RIGHT_MERGIN (printf("%3c\n", ' '))

int draw_rect(int, int);

int main()
{
	system("clear");
	
	char ch = 'a', nxt;
	int line = 1, i, j, page = 0;
	const char filename[] = "sample_files/sample1.txt";

	FILE *fp;
	fp = fopen(filename, "r");
	if(fp == NULL)
	{
		printf("File can not open\n");
		exit(1);
	}

	while(1)
	{	
		draw_rect(_LENGTH, _HEIGHT);
		for(i = 0; i < _HEIGHT-1; ++i)
			printf("\r\033[1A"); //reset cursor

		//line 2; contains file name and page no.
		_LEFT_MERGIN;
		printf("%-64sPage %-3d", filename, ++page);
		_RIGHT_MERGIN;
	
		//line 3; Blank line
		_LEFT_MERGIN;
		for(i = 3; (i < _LENGTH-4) && (ch != EOF); ++i)
			putchar(' ');
		_RIGHT_MERGIN;

		//line 4 to 22; file contents
		for(i = 3; i < _HEIGHT-1; ++i)
		{
			if (ch == EOF)
				putchar('\n');
			else
			{
				_LEFT_MERGIN;
				for(j = 3; j < _LENGTH-4; ++j)	
				{
					ch = fgetc(fp);
					if (ch == EOF || ch == '\n')
						break;	
					else
						putchar(ch);
				}
				_RIGHT_MERGIN;
			}
		}

		if (ch == EOF)
		{	
			//line 23; bottom side of the rectangle 
			putchar('|');
			for (i = 0; i < _LENGTH-2; ++i)
				putchar('_');
			printf("|\nEnd Of File%20c\n", ' ');

			exit(0);
		}

		printf("\nPress enter to goto next page\n");
		printf("Enter any other key to exit\n");
		scanf("%c", &nxt);
	
		if (nxt == '\n')
		{
			// move cursor up to 2nd line
			for(i = 0; i < _HEIGHT + 4; ++i)
				printf("\r\033[1A");
		}
		else 
			exit(0);
	}
}

int draw_rect(int l, int h)
{
	char s1[l+1];
	sprintf(s1, "|%%%dc|\n", l-2);
	const char *s2 = s1;
	
	for (int i = 1; i <= h; ++i) {
		if (i != 1 && i != h)
		{
			printf(s2, ' ');
			continue;
		}
		else {
			for(int j = 1; j <= l; ++j)
			{
				if (j == 1 || j == l)
				{
					if (i == 1)
						putchar(' ');
					else
						putchar('|');
				}
				else 	
					putchar('_');
			}
		}

		putchar('\n');
	}
	return 0;	
}
