// To determine whether the input char is small case, upper case, a digit or a symbol

#include <stdio.h>

int main()
{
	char x;

	printf("Enter a charecter\n");
	scanf("%c", &x);

	if(x>=65 && x<=90)
		printf("Upper Case Letter\n");
	else if(x>=97 && x<=122)
		printf("Lower caser Letter\n");
	else if(x>=48 && x<=57)
		printf("It's a Digit\n");
	else
		printf("Special Symbol\n");

	return 0;
}
