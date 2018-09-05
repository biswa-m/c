// reverse the digit and check pelindrom or not

#include <stdio.h>

int main()
{
	int n, rev;

	printf("Enter a five digit no \n");
	scanf("%d", &n);

	rev = n/1%10*10000 + n/10%10*1000 + n/100%10*100 + n/1000%10*10 + n/10000%10;

	printf("The reversed no is %d\n", rev);

	if(n==rev)
		printf("The no is Pelindrom");
	else
		printf("The no is not Pelindrom");

	return 0;
}
