// To calculate area of a triangle when length of sides are input

#include <stdio.h>
#include <math.h>

int main()
{
	float s1, s2, s3, Area, s;

	printf("Enter the lengths of three sides of the triangle \n");
	scanf("%f %f %f", &s1, &s2, &s3);

	//formula
	s = (s1+s2+s3)/2;
	Area = sqrt(s*(s-s1)*(s-s2)*(s-s3));

	printf("The area of the triangle is %.3f\n", Area);

	return 0;
}
