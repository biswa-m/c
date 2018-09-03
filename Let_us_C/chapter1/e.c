// calculate area and perimeter/cicumference

#include <stdio.h>

int main()
{
	float l, b, r, C, A_circle, A_rect, P;

	//For rectangle
	printf("Enter length and breadth of the rectangle \n");
	scanf("%f %f", &l, &b);
	
	//formula
	A_rect = l * b; 
	P=2*(l+b);

	printf("Area = %.2f, Perimeter = %.2f\n", A_rect, P);

	//for circle
	printf("Enter the radius of the circle \n");
	scanf("%f",&r);

	//formula
	A_circle = 3.1416 * r * r;
	C = 2 * 3.1416 * r;

	printf("Area = %.2f, Cercumference = %.2f\n", A_circle, C);

	return 0;
}
