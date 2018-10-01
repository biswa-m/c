#include <stdio.h>

int main()
{
	int n[3][3] = {	2, 4, 3,
			6, 8, 5,
			3, 5, 1
			};
	printf("%d %d %d %d\n", *n, &n[0], n[3][3], n[2][2]);
}
