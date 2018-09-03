// calculate paper sizes of A1 to A8. Size of A0 is given.

#include <stdio.h>

int main()
{
	int l0, b0, l1, b1, l2, b2, l3, b3, l4, b4;

	l0 = 1189, b0 = 841; //for A0

	// A(n) is defined as A(n-1) cut in half, parallel to its shorter sides.
	l1 = b0, b1 = l0/2; 
	l2 = b1, b2 = l1/2; 
	l3 = b2, b3 = l2/2; 
	l4 = b3, b4 = l3/2; 

	printf("Paper sizes are \n A0 = %dx%d\n A1 = %dx%d\n A2 = %dx%d\n A3 = %dx%d\n A4 = %dx%d\n",l0,b0,l1,b1,l2,b2,l3,b3,l4,b4);
	
	return 0;
}
