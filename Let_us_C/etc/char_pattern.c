// print character Pattern 

#include <stdio.h>

int main()
{
	int i, j, blank='G', flag;

	for(i=0; i<7; i++)
	{
		j = 'A';
		flag = 0;

		while(j>='A')
		{
			(j > blank) ? printf("  "):printf("%c ", j);

			if(j < 'G' && flag == 0) 	
				j++;	
			else	
				j--, flag = 1;
		}
		
		printf("\n");
		blank--;
	}

	return 0;
}
		

