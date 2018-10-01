/* Twenty-five numbers are entered from the keyboard into an array. 
 * Write a program to find out how many of them are positive, 
 * how many are negative, how many are even and how many odd.
 */

#include <stdio.h>

#define SIZE 25

int main()
{
	printf("Enter %d no.s\n", SIZE);

	int array[SIZE], i = 0;
	char buf[1000];

	while (i < SIZE) {
		printf("%d:\t", i + 1);
	
		if (fgets(buf, sizeof buf, stdin) == NULL)
			continue;
		char *p = buf;
		int n;
		while (sscanf(p, "%d %n", &array[i], &n) == 1) {
			i++;
			p += n;
		}	
	}

	printf("The obtained array is \n");
	for (int i = 0; i < 25; ++i)
		printf("%d ", array[i]);

	int even, odd, pos, neg;
	even = odd = pos = neg = 0;

	for (int i = 0; i < 25; ++i) {
		(array[i] % 2) ? ++odd : ++even;
		(array[i] < 0) ? ++neg : ++pos;	
	}
		printf("\nEven = %d\tOdd = %d\n", even, odd);
		printf("Positive = %d\tNegative = %d\n", pos, neg);

	return 0;	
}
