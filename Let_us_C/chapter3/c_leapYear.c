// find out whether leap year or not

#include <stdio.h>

int main()
{
	int n;
	
	printf("Enter a year\t");
	scanf("%d", &n);

	if(n%4)
		printf(" The entered is not leap year \n");
	else if(n%100)
		printf(" The entered year is leap year \n");
	else if(n%400)
		printf(" The entered year is not leap year  \n");
	else
		printf(" The entered year is leap year \n");
	return 0; 
}
