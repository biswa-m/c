// To convert cartasian co-ordinate (x, y) of a point to polar (r, phi)

#include <stdio.h>
#include <math.h>

int main()
{
	float x, y, r, phi;

	printf("Enter the cartasian co-ordinate of the point\n");
	scanf("%f %f", &x, &y);
	
	//conversion formula 
	r = sqrt(x*x + y*y);
	phi = atan(y/x);
	printf("The conversion of cartasian co-ordinate (%.2f, %.2f) \nto polar co-ordinate is (%f, %f)\n", x, y, r, phi);

	return 0;
}
