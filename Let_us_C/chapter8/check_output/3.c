#include <stdio.h>

int main()
{
	int sub[50], i;
	for (i = 0; i <= 48; ++i) {
		sub[i] = i;
		printf("\t%d", sub[i]);	
	}
	int (*p)[] = sub;
	printf("\n==%d", **p);	
}
