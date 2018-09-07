#include <stdio.h>

int main()
{
	int n, i, j, flag, row, x;

	printf("Enter required no of row of the pattern\n");
	scanf("%d", &row);

	for (i=1; i<=row; i++)
	{
		x = i-1; // Every row will start with followed by x
		for (j = 1; j < 2*row; j++ )
		{
			if (j <= row-i) 	//Starting blank space
			{
				printf(" ");
				continue;
			}

			else if (j > row+i-1)	//Ending blank space
				break;
			
			else			//All numbers are in here
			{
				//first and last positions are always 1
				if ((j == row-i+1) || (j == row+i-1))
					printf("1");
			
				//in even lines odd positions are blank and 
				//in odd iines even posiitions are blank
				else if( (   j%2  && !(i%2) ) || 
					 ( !(j%2) &&   i%2  ) )
					printf(" ");

				else if (j < row)
				{
					printf("%d", x);
					x += 2;
				}

				else if (j%2 == 0) 
				{
					x -= 2;
					printf("%d", x);
				}

				else 
				{
					printf("%d", x);
					x -= 2;
				}
			}
		}
		printf("\n");
	}
}
