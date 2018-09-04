// input temperature and wind velocity and calculate Wind Chill Factor.
// wcf = 35.74 + 0.6215t + (0.4275t-35.75)*v^0.16

#include <stdio.h>
#include <math.h>

int main()
{
	float wcf, t, v;

	printf("Enter the value of temperature and wind speed respectively\n");
	scanf("%f %f", &t, &v);	

	wcf = 35.74 + 0.6215*t + (0.4275*t - 35.75)*pow(v, 0.16);

	printf("Wind chill factor = %f\n", wcf);

	return 0;	
}

