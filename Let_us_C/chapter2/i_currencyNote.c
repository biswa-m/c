// sum of rupees is input. WAP to compute smallest no of notes that will combine to give the sum.
// Denominations -> 1, 2, 5, 10, 50, 100

#include <stdio.h>

int main()
{
	int sum, n1, n2, n5, n10, n50, n100, rem;

	printf("Enter the sum of rupees \n");
	scanf("%d", &sum);


	/* Method 1
	n100 = sum/100;
	n50 = sum%100/50;
	n10 = sum%100%50/10;
	n5 = sum%100%50%10/5;
	n2 = sum%100%50%10%5/2;
	n1 = sum%100%50%10%5%2; */

	n100 = sum/100, rem = sum % 100;
	n50 = rem/50, rem = rem % 50;
	n10 = rem/10, rem = rem % 10;
	n5 = rem/5, rem = rem % 5;
	n2 = rem/2, rem = rem % 2;
	n1 = rem;

	printf("The combination for smallest no of notes is \n%dx100\n%dx50\n%dx10\n%dx5\n%dx2\n%dx1", n100, n50, n10, n5, n2, n1);

	return 0;
		
}
