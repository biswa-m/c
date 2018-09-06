// To print all the prime numbers from 1 to 300

#include <stdio.h>

int main()
{
	int num, j, upto = 300;

	for(num =2; num <= upto; num++)
	{
		j = 2;
		while(1)
		{
			if ((num % j == 0)  && (j != num))
				break;
			else if(j ==  num)
			{
				printf("%d ", num);
				break;
			}
			j++;
		}
	}
	printf("\n");

	return 0;
}
