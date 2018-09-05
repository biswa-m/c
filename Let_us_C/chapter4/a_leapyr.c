// TO check leap year using && and ||

#include <stdio.h>

int main()
{
	int yr;

	printf("Enter any year to check leap year or not \n");
	scanf("%d", &yr);
	
	if( !(yr%4) && ( yr%100 || !(yr%100) && !(yr%400)) )
		printf("Leap Year \n");
	else
		printf("Not Leap Year");
}
