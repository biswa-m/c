// sum of digit of a five digit no

#include <stdio.h>

int main()
{
	int n, sum;

	printf("Enter a five digit no \n");
	scanf("%d", &n);

	sum = n % 10 + n/10%10 + n/100%10 + n/1000%10 + n/10000%10;

	printf(" The sum of the digits is %d \n", sum);

	return 0;
}
