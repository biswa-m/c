// input three angle of a triangle. Check it is valid or not

#include <stdio.h>

int main()
{
	float a, b, c;

	printf("Enter three angles to check that it will form a valid traingle or not. \n");
	scanf("%f %f %f", &a, &b, &c);

	if(a+b+c==180)
		printf("valid triangle \n");
	else
		printf("invalid triangle \n");

	return 0;
}
