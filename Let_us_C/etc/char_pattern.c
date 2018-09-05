// print  A B C D E F G F E D C B A

#include <stdio.h>

int main()
{
	int i, j, blank=71;

		for(i=0; i<7; i++)
		{
			for(j=65; j<72; j++)
				(j > blank) ? printf("  "):printf("%c ", j);
			for(j=70; j>=65; j--)
				(j > blank) ? printf("  "):printf("%c ", j);
		printf("\n");

		blank--;
	}

	return 0;
}
		

