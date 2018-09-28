#include <stdio.h>

circle(int r)
{
	float a;
	a = 3.14 * r * r;
	return a;
}

int main()
{
	float area;
	int radius = 1;
	area = circle(radius);
	printf("\n%f", area);
}
