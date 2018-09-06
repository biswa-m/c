// To print all the prime numbers from 1 to 300

#include <stdio.h>

int main()
{
	int num, j, count = 0, upto = 300;

	for(num =2 ; num <= upto; num++)
	{
		for(j = 1, count = 0; (j <= num && count <= 2); j++)
		{
			if (num % j == 0)
			{
				count++;
				if (count == 2 && j == num)
				{
					printf(" %d", num);
					break;
				}

			}
		}
	}
	printf("\n");

	return 0;
}
