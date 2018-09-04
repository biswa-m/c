// find out whether even or odd

#include <stdio.h>

int main()
{
	int n;
	
	printf("Enter an integer \t");
	scanf("%d", &n);

	if(n%2)
		printf(" The entered no is Odd \n");
	else
		printf(" The entered no is even \n");

	return 0; 
}
