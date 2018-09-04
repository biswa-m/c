// reverse the digit of a five digit no

#include <stdio.h>

int main()
{
	int n, rev;

	printf("Enter a five digit no \n");
	scanf("%d", &n);

	/* let n=12345  
	 * to make 2nd digit as 4th digit 
	 * n/10 = 1234
	 * n/10%10 = 4
	 * n/10%10*1000 = 4000
	 */
	rev = n/1%10*10000 + n/10%10*1000 + n/100%10*100 + n/1000%10*10 + n/10000%10;

	printf("The reversed no is %d\n", rev);

	return 0;
}
