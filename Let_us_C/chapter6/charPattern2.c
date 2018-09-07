// Pascal's triangle

#include <stdio.h>

int main()
{
	int i, j, diff, row, x;

	printf("Enter required no of row of the pattern\n");
	scanf("%d", &row);

	for (i=1; i<=row; i++)
	{
		diff = 1;
		x = i-2; 

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
				if (j == row)
					diff = -1;

				//first and last positions are always 1
				if ((j == row-i+1) || (j == row+i-1))
					printf("1");
			
				//odd positions from stating char are blank
				else if ((j - (row-i+1)) % 2)
				{
					printf(" ");
					x += diff;
				}
				else 
				{
					printf("%d", x);
					x += diff;
				}
			}
		}
		printf("\n");
	}
}
