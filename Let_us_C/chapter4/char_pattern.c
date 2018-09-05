// print  A B C D E F G F E D C B A

#include <stdio.h>

int main()
{
        int i, j=65, flag=0;

	//for(i=0; i<13; i++)
	while(j != 64)
	{
		printf("%c ", j);
		
		if(j < 71 && flag == 0) 
			j++;
		else
		{
			flag =1;
			j--;
		}
	}
	printf("\n");

	return 0;
}
		

