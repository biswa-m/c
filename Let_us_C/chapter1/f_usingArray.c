// calculate paper sizes of A1 to A8. Size of A0 is given.

#include <stdio.h>

int main()
{
        int l[9], b[9], n;

        l[0] = 1189, b[0] = 841; //for A0

	printf("Paper sizes are\nA0 = %dx%d \n", l[0], b[0]);

        // A(n) is defined as A(n-1) cut in half, parallel to its shorter sides.
	for(n=1;n<=8;n++)
	{
		l[n] = b[n-1];
		b[n] = l[n-1]/2;

		printf("A%d = %dx%d\n", n, l[n], b[n]);
	}

        return 0;
}

